/* ButtonP.h - Private Button widget declaration
 *
 * Copyright (C) 1998  Jochen Voss.
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
