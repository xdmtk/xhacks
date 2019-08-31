/* starscape, Copyright (c) 2019 Nick Martinez <nick@xdmtk.org>
*
* Permission to use, copy, modify, distribute, and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice appear in all copies and that both that
* copyright notice and this permission notice appear in supporting
* documentation.  No representations are made about the suitability of this
* software for any purpose.  It is provided "as is" without express or
* implied warranty.
*/

#include <math.h>
#include <assert.h>
#include "screenhack.h"
#include "alpha.h"
#include "../clion_include/X.h"
#include "../clion_include/Xlib.h"

#define DBG 1
#define max(a,b) (a>b?a:b)
#define countof(x) (sizeof(x)/sizeof(*(x)))
#define ABS(x) ((x)<0?-(x):(x))
#define toradians(x) ((x * (M_PI/180)))
#define todegrees(x) ((x * (180/M_PI)))
struct origin_field{
    XPoint ul, ur, bl, br;
};

struct star {
    XPoint location;
    int brightness, speed;
    double direction;
};

struct state {
    Display *dpy;
    Window window;
    struct origin_field origin;
    XColor *colors, last_color;
    GC gc;
    XWindowAttributes xgwa;
    Colormap colormap;
    XGCValues gcv;
    struct star * stars;
    int window_w, window_h, delay, star_count;
    XPoint center_screen;


};

static void init_origin(struct state * st) {

    /* Setup a square field in the center of the screen as origin for star generation */
    st->origin.ul.y = st->origin.ur.y = (st->window_h/2)-(int)(st->window_h*.25);
    st->origin.bl.y = st->origin.br.y = (st->window_h/2)+(int)(st->window_h*.25);
    st->origin.ul.x = st->origin.bl.x = (st->window_w/2)-(int)(st->window_w*.25);
    st->origin.ur.x = st->origin.br.x = (st->window_w/2)+(int)(st->window_w*.25);
}

static int get_brightness_from_origin(struct state * st, int x, int y) {

    /* Using the furthest point from the origin (x or y) we can calculate the percentage of the
     * offset, and multiply it against the 256 alpha value to get our brightness
     * The closer to the origin, the darker the star */
    int max_distance = max(ABS(x - st->center_screen.x), ABS(y - st->center_screen.y));

    if (ABS(x - st->center_screen.x) > ABS(y - st->center_screen.y)) {
        return (int)(max_distance/st->center_screen.x)*256;
    }
    return (int)(max_distance/st->center_screen.y)*256;
}

static double get_direction_from_origin(struct state * st, int x, int y) {
    double slope = (double)(y - st->center_screen.y)/(double)(x - st->center_screen.x);
    printf("(%d, %d) - Slope: %f - Angle: %f - Center is at (%d, %d) \n", x, y, slope, atan(slope), st->center_screen.x, st->center_screen.y);
    printf("center y: %d\n", st->center_screen.y);
    printf("center x: %d\n", st->center_screen.x);
    return atan(slope);

}

static void generate_initial_stars(struct state * st) {

    /* Generate an initial set of stars and place them in the origin field */
    int i, initial_stars = random() % 10; st->star_count = initial_stars;
    st->stars = (struct star *) malloc(sizeof(struct star)*initial_stars);
    assert(st->stars);

    for (i = 0; i < initial_stars; ++i) {
        struct star s;
        s.location.x = random() % st->origin.ur.x; s.location.y = random() % st->origin.bl.y;
        while (s.location.x < st->origin.ul.x || s.location.y < st->origin.ul.y) {
            if (s.location.x < st->origin.ul.x)
                s.location.x = random() % st->origin.ur.x;
            if (s.location.y < st->origin.ul.y)
                s.location.y = random() % st->origin.bl.y;
        }
        printf("For star #%d: ", i);
        s.direction = get_direction_from_origin(st, s.location.x, s.location.y);
        s.brightness = get_brightness_from_origin(st, s.location.x, s.location.y);
        s.speed = s.brightness; /* Speed is proportional to brightness ( brighter stars will move faster ) */
        st->stars[i] = s;
    }
}

static void * starscape_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));
    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 60000;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);


    /* Get the dimensions of the window */
    st->window_w = st->xgwa.width;
    st->window_h = st->xgwa.height;
    printf("Window height: %d\n", st->xgwa.height);
    printf("Window width: %d\n", st->xgwa.width);
    st->center_screen.x = st->window_w/2; st->center_screen.y = st->window_h/2;
    printf("center y: %d\n", st->center_screen.y);
    printf("center x: %d\n", st->center_screen.x);


    init_origin(st);
    /* Setting up the colormap. not exactly sure what this does yet */
    st->colormap = st->xgwa.colormap;
    /* Variable to hold properties that we can attribute the the Graphics Context ( GC ) */
    st->gcv.foreground = WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy));
    st->gcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));

    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &st->gcv);

    generate_initial_stars(st);
    return st;
}

static void move_stars(struct state * st) {

    int i;

    XSetForeground(st->dpy, st->gc, BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy)));
    XFillRectangle(st->dpy, st->window, st->gc, 0,0,st->window_w, st->window_h);
    for (i = 0; i < st->star_count; ++i) {
        st->stars[i].location.x -= cos(st->stars[i].direction)*(st->stars[i].location.x > st->center_screen.x ? -5 : 5);
        st->stars[i].location.y -= sin(st->stars[i].direction)*(st->stars[i].location.x > st->center_screen.x ? -5 : 5);
        printf("Star #%d: (%d,%d)\n", i, st->stars[i].location.x, st->stars->location.y);
    }
}

static unsigned long starscape_draw (Display *dpy, Window window, void *closure) {
    struct state *st = (struct state *) closure;
    int i;
    char buf[] = {'\0', '\0','\0'};
    move_stars(st);
    XSetForeground(st->dpy, st->gc, WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy)));
    for (i = 0; i < st->star_count; ++i) {
        sprintf(buf, "%d", i);
        XDrawString(st->dpy, st->window, st->gc, st->stars[i].location.x, st->stars[i].location.y, buf, 1 );
    }
#ifdef DBG
    XSetForeground(st->dpy, st->gc, WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy)));
    XDrawLine(st->dpy, st->window, st->gc, 0, st->center_screen.y, st->window_w, st->center_screen.y);
    XDrawLine(st->dpy, st->window, st->gc, st->center_screen.x, 0, st->center_screen.x, st->window_h);
#endif

    return st->delay;
}

static void starscape_reshape (Display *dpy, Window window, void *closure,
        unsigned int w, unsigned int h) {

    struct state *st = (struct state * ) closure;
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

    st->window_w = st->xgwa.width; st->window_h  = st->xgwa.height;
    init_origin(st);
    return;
}

static Bool starscape_event (Display *dpy, Window window, void *closure, XEvent *event) {
    return False;
}

static void starscape_free (Display *dpy, Window window, void *closure) {
    struct state *st = (struct state *) closure;
    free (st);
}


static const char *starscape_defaults [] = {
    "*delay: 10000000"
};

static XrmOptionDescRec starscape_options [] = {
    {"-delay",          ".delay",       XrmoptionSepArg, 0 }
};


XSCREENSAVER_MODULE ("Starscape", starscape)
