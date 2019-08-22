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

    /* Default display given to us by Xscreensaver */
    st->dpy = dpy;

    /* Default window given to us by Xscreensaver */
    st->window = window;

    st->delay = 10000000;

    st->init = 0;

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
    st->gcv.foreground = WhitePixelOfScreen(DefaultScreenOfDisplay(st->dpy));
    st->gcv.background = BlackPixelOfScreen(DefaultScreenOfDisplay(st->dpy));

    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground, &st->gcv);
    return st;

}


static void find_square_coords(struct rect *r, struct square *s) {
    /* Determine orientation of rectangle */
    if (abs(r->ul.x - r->ur.x) < abs(r->ul.y - r->bl.y))  {
        printf("Longer\n");
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
    }
    else {
        printf("Wider\n");
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
    }

}



static void draw_golden_rect(struct state *st) {
    find_square_coords(&st->rect_coords, &st->square_coords);
    printf("Rectangle:\n"
            "UL: (%d,%d)\n"
            "UR: (%d,%d)\n"
            "BL: (%d,%d)\n"
            "BR: (%d,%d)\n"
            "Square:\n"
            "UL: (%d,%d)\n"
            "UR: (%d,%d)\n"
            "BL: (%d,%d)\n"
            "BR: (%d,%d)\n",
           st->rect_coords.ul.x,
           st->rect_coords.ul.y,
           st->rect_coords.ur.x,
           st->rect_coords.ur.y,
           st->rect_coords.bl.x,
           st->rect_coords.bl.y,
           st->rect_coords.br.x,
           st->rect_coords.br.y,

           st->square_coords.ul.x,
           st->square_coords.ul.y,
           st->square_coords.ur.x,
           st->square_coords.ur.y,
           st->square_coords.bl.x,
           st->square_coords.bl.y,
           st->square_coords.br.x,
           st->square_coords.br.y
    );
    st->gcv.line_width = 5;
    st->gc = XCreateGC(st->dpy, st->window, GCForeground | GCBackground | GCLineWidth, &st->gcv);
    random_color(st);

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
    draw_golden_rect(st);
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
