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
    int width, height;
    int x1, y1, x2, y2, complete, ystart;
};



static void * fibonacci_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));

    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 100;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

    /* Get the dimensions of the window */
    st->width = st->xgwa.width;
    st->height = st->xgwa.width;

    /* Setting up the colormap. not exactly sure what this does yet */
    st->colormap = st->xgwa.colormap;

    XGCValues gcv;
    /* Variable to hold properties that we can attribute the the Graphics Context ( GC ) */
    gcv.foreground = WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy));
    gcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));

    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &gcv);
    st->x1 = st->y1 = st->y2 = st->x2 = st->ystart = 0;

    return st;

}

static unsigned long fibonacci_draw (Display *dpy, Window window, void *closure) {

    struct state *st = (struct state *) closure;
    if (!st->complete) {
        st->x2 += 1;
        st->complete = st->x2 > st->width ? 1 : 0;
    }
    else {
        st->y1 += 100;
        st->y2 += 100;
        st->x1 = st->x2 = 0;
        st->complete = 0;
    }
    if (st->y1 > st->height) {
        st->ystart += 10;
        st->y1 = st->y2 = st->ystart;
    }
    XColor xcolour;

    xcolour.red = random() % 65000 ; xcolour.green = random() % 65000; xcolour.blue = random() % 65000;
    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(st->dpy, st->colormap, &xcolour);

    XSetForeground(st->dpy, st->gc, xcolour.pixel);
    XDrawLine(st->dpy, st->window, st->gc, st->x1, st->y1, st->x2, st->y2 + (sin(st->x2) * st->height));
    return st->delay + 100;
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
