/* pixmapdimen.c - get the extents of a X window system pixmap
 *
 * Copyright (C) 1998, 2013  Jochen Voss
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
