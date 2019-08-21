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

#ifdef HAVE_DOUBLE_BUFFER_EXTENSION
# include "xdbe.h"
#endif /* HAVE_DOUBLE_BUFFER_EXTENSION */

#define countof(x) (sizeof(x)/sizeof(*(x)))
#define ABS(x) ((x)<0?-(x):(x))

struct state {
  Display *dpy;
  Window window;

  Bool transparent_p;
  Bool dbuf;
  XColor *colors;
  GC erase_gc;
  XWindowAttributes xgwa;

};


static void

static void *
fibonacci_init (Display *dpy, Window window)
{
  struct state *st = (struct state *) calloc (1, sizeof(*st));
  XGCValues gcv;
  int i;
  st->dpy = dpy;
  st->window = window;
  XGetWindowAttributes (st->dpy, st->window, &st->xgwa);

  st->colors = (XColor *) calloc (sizeof(*st->colors), st->ncolors);
  return st;

}

static unsigned long
fibonacci_draw (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  int i;
  return st->delay;
}

static void
fibonacci_reshape (Display *dpy, Window window, void *closure,
                 unsigned int w, unsigned int h)
{
    return;
}

static Bool
fibonacci_event (Display *dpy, Window window, void *closure, XEvent *event)
{
  return False;
}

static void
fibonacci_free (Display *dpy, Window window, void *closure)
{
  struct state *st = (struct state *) closure;
  int i;
  XFreeGC (dpy, st->erase_gc);
  if (st->ba) XFreePixmap (dpy, st->ba);
  if (st->bb) XFreePixmap (dpy, st->bb);
  if (st->plane_masks) free (st->plane_masks);
  for (i = 0; i < st->count; i++)
    if (st->throbbers[i]) {
      XFreeGC (dpy, st->throbbers[i]->gc);
      free (st->throbbers[i]);
    }
  free (st->throbbers);
  free (st->colors);
  free (st);
}


static const char *fibonacci_defaults [] = {
};

static XrmOptionDescRec fibonacci_options [] = {
};


XSCREENSAVER_MODULE ("Fibonacci", fibonacci)
