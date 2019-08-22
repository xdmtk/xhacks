/* xscreensaver, Copyright (c) 1999-2018 Jamie Zawinski <jwz@jwz.org>
*
* Permission to use, copy, modify, distribute, and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice appear in all copies and that both that
* copyright notice and this permission notice appear in supporting
* documentation.  No representations are made about the suitability of this
* software for any purpose.  It is provided "as is" without express or
* implied warranty.
*/

#include "../clion_include/Xlib.h"
#include "../clion_include/X.h"

#include <math.h>
#include "screenhack.h"
#include "alpha.h"


#define countof(x) (sizeof(x)/sizeof(*(x)))
#define ABS(x) ((x)<0?-(x):(x))

struct state {
    Display *dpy;
    Window window;

    XColor *colors;
    GC gc;
    XWindowAttributes xgwa;
    Colormap colormap;
    XGCValues gcv;

    unsigned long delay;
    int width, height, initial_width, initial_x;
    int init;
    int w_l_switch, blackout_pause;

    struct rect {
        XPoint ul, ur, bl, br;
    } rect_coords;

    struct square {
        XPoint ul, ur, bl, br;
    } square_coords;

};

static int get_initial_x(int sw, int iw) {
   return (sw - iw)/2;
}

static int get_initial_width(int w, int h) {
    float fw = (float)w; float fh = (float)h;
    for (;;) {
        if (fw*1.618 < fh)
            return (int)fw;
        fw--;
    }
}

static XColor generate_color(char * color_str) {
    XColor color; char red_buf[3]; char green_buf[3]; char blue_buf[3];
    memcpy(red_buf, &color_str[0], 2); red_buf[2] = '\0';
    memcpy(green_buf, &color_str[2], 2); green_buf[2] = '\0';
    memcpy(blue_buf, &color_str[4], 2); blue_buf[2] = '\0';

    color.red = (int)strtol(red_buf, NULL, 16 ) << 8;
    color.green = (int)strtol(green_buf, NULL, 16 ) << 8;
    color.blue = (int)strtol(blue_buf, NULL, 16 ) << 8;

    printf("%d %d %d\n", color.red, color.green, color.blue);
    color.flags = DoRed | DoGreen | DoBlue;

    return color;
}

static void random_color(struct state *st) {

    XColor color = st->colors[random() % 15];
/*    color.red = 0x7F << 8; color.green = 0xFF << 8; color.blue = 0x0 << 8; */
    XAllocColor(st->dpy, st->colormap, &color);
    XSetForeground(st->dpy, st->gc, color.pixel);
}
static void init_colors(struct state *st) {
    XColor xcm[15] = {
        generate_color("FFA500"),
        generate_color("FF0F55"),
        generate_color("FFBBBB"),
        generate_color("FFCBCB"),
        generate_color("FF3320"),
        generate_color("FFBA02"),
        generate_color("FFBC66"),
        generate_color("FFDBBD"),
        generate_color("FFF000"),
        generate_color("FD00FF"),
        generate_color("FF0392"),
        generate_color("FFBB03"),
        generate_color("FF2090"),
        generate_color("FF1203"),
        generate_color("FF2390"),
    };
    st->colors = xcm;
}
static void * fibonacci_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));

    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 200000;

    st->init = st->blackout_pause = 0;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

    /* Get the dimensions of the window */
    st->width = st->xgwa.width;
    st->height = st->xgwa.height;

    st->initial_width = get_initial_width(st->width, st->height);
    st->initial_x = get_initial_x(st->width, st->initial_width);


    /* Set initial vertices for first square */

    /* Setting up the colormap. not exactly sure what this does yet */
    st->colormap = st->xgwa.colormap;
    /* Variable to hold properties that we can attribute the the Graphics Context ( GC ) */
    st->gcv.foreground = WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy));
    st->gcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));

    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &st->gcv);
    init_colors(st);
    return st;

}


static int find_square_coords(struct rect *r, struct square *s, int * wls) {
    /* Determine orientation of rectangle */
    if (abs(r->ul.x - r->ur.x) < abs(r->ul.y - r->bl.y))  {
        if (*wls)
            return 0;
        /* If our rectangle is longer than it is wide, our square
         * will have side length of the x distance, the top corners
         * can stay the same as the rectangle */
        s->ul = r->ul; s->ur = r->ur;
        s->bl.x = r->bl.x; s->bl.y = r->ul.y + abs(r->ul.x - r->ur.x);
        s->br.x = r->br.x; s->br.y = s->bl.y;

        /* Now we need to find the new rectangle, which in this case
         * all we need to do is move the top of the rectangle corners
         * to the bottom of the square */
        r->ul = s->bl ; r->ur = s->br;
        *wls = 1;
    }
    else {
        if (!*wls)
            return 0;
        /* If our rectangle is wider than it is long, our square
         * will have side length of the y distance, so our left corners
         * can stay the same as the rectangle */
        s->ul = r->ul ; s->bl = r->bl;

        /* But our right corners need to be moved the y distance of
         * the rectangle */
        s->ur.y = r->ur.y ; s->ur.x = s->ul.x + abs(r->ul.y - r->bl.y);
        s->br.y = r->br.y ; s->br.x = s->ur.x;

        /* Now we need to find the new rectangle, which for a wide
         * rectangle, would be the moving the left corners of the rect
         * to the right corners of the square */
        r->ul = s->ur ; r->bl = s->br;
        *wls = 0;
    }
    return 1;

}



static int draw_golden_rect(struct state *st) {
    if (!find_square_coords(&st->rect_coords, &st->square_coords, &st->w_l_switch)) {
        if (!st->blackout_pause) {
            st->blackout_pause = !st->blackout_pause;
            return 0;
        }
        st->blackout_pause = !st->blackout_pause;
        st->initial_width = get_initial_width(st->width, st->height);
        st->initial_x = get_initial_x(st->width, st->initial_width);
        st->init = !st->init;
        XGCValues t_xgcv;
        t_xgcv.foreground = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));
        t_xgcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));
        st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &t_xgcv);
        random_color(st);
        XFillRectangle(st->dpy, st->window, st->gc, 0, 0, st->width, st->height);
        if (st->height < st->width )  {
            st->w_l_switch = 0;
        }
        else {
            st->w_l_switch = 1;
        }
        return 0;

    }
    random_color(st);
    XPoint xp[] = {
            st->rect_coords.ul,
            st->rect_coords.ur,
            st->rect_coords.br,
            st->rect_coords.bl
    };

    XFillPolygon(st->dpy, st->window, st->gc,
            xp, 4, Convex, CoordModeOrigin);

    XSetForeground(st->dpy, st->gc, BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy)));
    XDrawLine(st->dpy, st->window, st->gc,
              st->rect_coords.ul.x, st->rect_coords.ul.y,
              st->rect_coords.ur.x, st->rect_coords.ur.y);
    XDrawLine(st->dpy, st->window, st->gc,
              st->rect_coords.ul.x, st->rect_coords.ul.y,
              st->rect_coords.bl.x, st->rect_coords.bl.y);
    XDrawLine(st->dpy, st->window, st->gc,
              st->rect_coords.br.x, st->rect_coords.br.y,
              st->rect_coords.bl.x, st->rect_coords.bl.y);
    XDrawLine(st->dpy, st->window, st->gc,
              st->rect_coords.br.x, st->rect_coords.br.y,
              st->rect_coords.ur.x, st->rect_coords.ur.y);

    return 1;
}

static unsigned long fibonacci_draw (Display *dpy, Window window, void *closure) {

    struct state *st = (struct state *) closure;
    random_color(st);
    if (!st->init) {

        /* Draw the first rectangle */
        XFillRectangle(st->dpy, st->window, st->gc, st->initial_x,
                       0, st->initial_width, st->height);

        /* Make Xpoints from the given coordinates */
        XPoint ul; ul.x = st->initial_x; ul.y = 0;
        XPoint ur; ur.x = st->initial_x + st->initial_width; ur.y = 0;
        XPoint bl; bl.x = st->initial_x; bl.y = st->height;
        XPoint br; br.x = st->initial_x + st->initial_width; br.y = st->height;

        /* Set the coordinates of the first rectangle and use it to find the
         square */
        st->rect_coords.ul = ul; st->rect_coords.ur = ur;
        st->rect_coords.bl = bl; st->rect_coords.br = br;

        st->init = !st->init;

    }
    if (!draw_golden_rect(st)) {
        return st->delay + 5000000;
    }
    return st->delay;
}

static void fibonacci_reshape (Display *dpy, Window window, void *closure,
        unsigned int w, unsigned int h) {

    return;
}

static Bool fibonacci_event (Display *dpy, Window window, void *closure, XEvent *event) {
    return False;
}

static void fibonacci_free (Display *dpy, Window window, void *closure) {
    struct state *st = (struct state *) closure;
    int i;
    free (st);
}


static const char *fibonacci_defaults [] = {
    "*delay: 10000000"
};

static XrmOptionDescRec fibonacci_options [] = {
    {"-delay",          ".delay",       XrmoptionSepArg, 0 }
};


XSCREENSAVER_MODULE ("Fibonacci", fibonacci)
