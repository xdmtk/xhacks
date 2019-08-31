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

#define countof(x) (sizeof(x)/sizeof(*(x)))
#define ABS(x) ((x)<0?-(x):(x))
struct origin_field{
    XPoint ul, ur, bl, br;
};

struct star {
    XPoint location;
    int direction, brightness, speed;
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


};

static void init_origin(struct state * st) {
    /* Setup a square field in the center of the screen as origin for star generation */
    st->origin.ul.y = st->origin.ur.y = (st->window_h/2)-(int)(st->window_h*.25);
    st->origin.bl.y = st->origin.br.y = (st->window_h/2)+(int)(st->window_h*.25);
    st->origin.ul.x = st->origin.bl.x = (st->window_w/2)-(int)(st->window_w*.25);
    st->origin.ur.x = st->origin.br.x = (st->window_w/2)+(int)(st->window_w*.25);
}

static void generate_initial_stars(struct state * st) {
    int i, initial_stars = random() % 100; st->star_count = initial_stars;
    st->stars = (struct star *) malloc(sizeof(struct star)*initial_stars);
    assert(st->stars);
    printf("Origin X Points: (%d, %d)\nOrigin Y Points:(%d, %d)\n", st->origin.ul.x, st->origin.ur.x,
        st->origin.ul.y, st->origin.bl.y );
    for (i = 0; i < initial_stars; ++i) {
        struct star s;
        s.location.x = random() % st->origin.ur.x; s.location.y = random() % st->origin.bl.y;
        while (s.location.x < st->origin.ul.x || s.location.y < st->origin.ul.y) {
            if (s.location.x < st->origin.ul.x)
                s.location.x = random() % st->origin.ur.x;
            if (s.location.y < st->origin.ul.y)
                s.location.y = random() % st->origin.bl.y;
        }
        st->stars[i] = s;
        printf("Star location: (%d, %d)\n", st->stars[i].location.x, st->stars[i].location.y);
    }
}

static void * starscape_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));
    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 200000;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);


    /* Get the dimensions of the window */
    st->window_w = st->xgwa.width;
    st->window_h = st->xgwa.height;

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

static void move



static unsigned long starscape_draw (Display *dpy, Window window, void *closure) {
    struct state *st = (struct state *) closure;
    int i;
    XSetForeground(st->dpy, st->gc, WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy)));

    for (i = 0; i < st->star_count; ++i)
        XDrawPoint(st->dpy, st->window, st->gc, st->stars[i].location.x, st->stars[i].location.y);

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
    int i;
    free (st);
}


static const char *starscape_defaults [] = {
    "*delay: 10000000"
};

static XrmOptionDescRec starscape_options [] = {
    {"-delay",          ".delay",       XrmoptionSepArg, 0 }
};


XSCREENSAVER_MODULE ("Starscape", starscape)
