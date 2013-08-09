/* ButtonP.h - Private Button widget declaration
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

#ifndef FILE_BUTTONP_H_SEEN
#define FILE_BUTTONP_H_SEEN

#include "Button.h"
#include <X11/CoreP.h>

#define XtRIcon "Icon"

struct icon {
  Pixmap  foreground, mask;
};

/* New fields for the Button widget record */
typedef  struct {
  /* Settable resources */
  struct icon  icon, active_icon;
  XtCallbackList  callbacks;
  Boolean  shape_window;

  /* Data derived from resources */
  GC  gc;
  Boolean  set, auto_width, auto_height, update_shape;
  Position  normal_x, normal_y, active_x, active_y;
} ButtonPart;

/* Full instance record definition */
typedef  struct _ButtonRec {
  CorePart core;
  ButtonPart button;
} ButtonRec;

/* New fields for the Button widget class record */
typedef  struct {
  XtPointer  extension;
} ButtonClassPart;

/* Full class record definition */
typedef  struct _ButtonClassRec {
  CoreClassPart core_class;
  ButtonClassPart button_class;
} ButtonClassRec;

/* Class record variable declaration */
extern  ButtonClassRec  buttonClassRec;

#endif /* not FILE_BUTTONP_H_SEEN */
