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

    unsigned long delay;
    int width, height, initial_width, initial_x;
    int init;
    int x, y, w, h, dir;
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

static void random_color(struct state *st) {

    XColor color;
    color.red = random() % 35000; color.green = random() % 24000;
    color.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(st->dpy, st->colormap, &color);
    XSetForeground(st->dpy, st->gc, color.pixel);
}

static void * fibonacci_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));

    XGCValues gcv;
    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 100;

    st->init = st->dir = 0;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

    /* Get the dimensions of the window */
    st->width = st->xgwa.width;
    st->height = st->xgwa.width;

    st->initial_width = get_initial_width(st->width, st->height);
    st->initial_x = get_initial_x(st->width, st->initial_width);


    /* Set initial vertices for first square */

    /* Setting up the colormap. not exactly sure what this does yet */
    st->colormap = st->xgwa.colormap;

    /* Variable to hold properties that we can attribute the the Graphics Context ( GC ) */
    gcv.foreground = WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy));
    gcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));

    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &gcv);
    return st;

}

/* 0 -> RIGHT , 1 -> DOWN , 2 -> LEFT, 3 -> UP */
static void draw_golden_rect(struct state *st) {

    char *coord_start, *coord_end;
    switch (st->dir) {
        case 0:
            asprintf(&coord_start, "Start (%d, %d) - End (%d, %d) ", st->x, st->y, st->w + st->x, st->w);
            XDrawString(st->dpy, st->window, st->gc, st->x, st->y, coord_start, strlen(coord_start));
            XDrawLine(st->dpy, st->window, st->gc,
                      st->x, st->w, st->w + st->x, st->w);
            st->dir = 1;
            st->x += st->h - st->w;
            st->y += st->w;
            st->h = st->h - st->w;
            st->w = st->w - st->h;
            break;
        case 1:
            asprintf(&coord_start, "Start (%d, %d) - End (%d, %d) ", st->x, st->y, st->x, st->h + st->y);
            XDrawString(st->dpy, st->window, st->gc, st->x, st->y, coord_start, strlen(coord_start));
            XDrawString(st->dpy, st->window, st->gc, st->x, st->y, "Hi", strlen("Hi"));
            XDrawLine(st->dpy, st->window, st->gc,
                      st->x, st->y, st->x, st->h + st->y);
            st->dir = 2;
            st->y += st->w;
            st->h = st->h - st->w;
            st->w += st->h - st->w;
            break;
        case 2:
            asprintf(&coord_start, "Start (%d, %d)", st->x, st->y);
            XDrawString(st->dpy, st->window, st->gc, st->x, st->y, coord_start, strlen(coord_start));
            XDrawString(st->dpy, st->window, st->gc, st->x, st->y, "Hi", strlen("Hi"));
            XDrawLine(st->dpy, st->window, st->gc,
                      st->x, st->y, st->w + st->x, st->h - st->y);
            st->dir = 2;
            st->y += st->w;
            st->h = st->h - st->w;
            st->w = st->h - st->h;
    }
}




static unsigned long fibonacci_draw (Display *dpy, Window window, void *closure) {

    struct state *st = (struct state *) closure;
    random_color(st);
    if (!st->init) {
        XDrawRectangle(st->dpy, st->window, st->gc, st->initial_x,
                       0, st->initial_width, st->height);
        st->init = !st->init;

        st->x = st->initial_x; st->y = 0;
        st->h = st->height; st->w = st->initial_width;
    }
    draw_golden_rect(st);
    return st->delay + 1000000;
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
