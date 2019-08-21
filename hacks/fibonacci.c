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
};



static void * fibonacci_init (Display *dpy, Window window) {

    /* Setup state variable */
    struct state *st = (struct state *) calloc (1, sizeof(*st));

    /* Variable to hold properties that we can attribute the the Graphics Context ( GC ) */
    XGCValues gcv;

    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    /* Using the window and display, we can find out all information we need about the window
     * we are going to draw on, and set it in xgwa ( x get window attributes) ) */
    XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

    /* Get the dimensions of the window */
    st->width = st->xgwa.width;
    st->height = st->xgwa.width;

    /* Setting up the colormap. not exactly sure what this does yet */
    st->colormap = st->xgwa.colormap;


    return st;

}

static unsigned long fibonacci_draw (Display *dpy, Window window, void *closure) {

    struct state *st = (struct state *) closure;
    int i;
    XDrawLine(st->dpy, st->window, st->gc, 50, 50 , 50 , 50);





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
    "*delay: 1000"
};

static XrmOptionDescRec fibonacci_options [] = {
    {"-delay",          ".delay",       XrmoptionSepArg, 0 }
};


XSCREENSAVER_MODULE ("Fibonacci", fibonacci)
