/* pixmapdimen.c - get the extents of a X window system pixmap
 *
 * Copyright (C) 1998  Jochen Voss.  */

static const  char  rcsid[] = "$Id$";


#include <X11/Xlib.h>
#include <X11/IntrinsicP.h>

#include "pixmapdimen.h"


void
get_pixmap_dimensions (Display *d, Pixmap pixmap,
		       unsigned *width_return, unsigned *height_return)
/* Return the width and height of PIXMAP in *WIDTH_RETURN and
 * *HEIGHT_RETURN.  */
{
  if (pixmap != None && pixmap != XtUnspecifiedPixmap) {
    Window  root;
    int  x, y;
    unsigned int  bw, depth;
    XGetGeometry(d, pixmap, &root, &x, &y,
		 width_return, height_return, &bw, &depth);
  } else {
    *width_return = *height_return = 0;
  }
}
