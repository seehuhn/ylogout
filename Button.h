/* Button.h - Public Button widget declaration
 *
 * Copyright (C) 1998  Jochen Voss.
 *
 * $Id$ */

#ifndef FILE_BUTTON_H_SEEN
#define FILE_BUTTON_H_SEEN

#include <X11/Core.h>

#define XtNicon "icon"
#define XtNactiveIcon "activeIcon"
#define XtCIcon "Icon"
#define XtNshapeWindow	"shapeWindow"
#define XtCShapeWindow	"ShapeWindow"

#define ButtonDefaultIcon "ButtonDefaultIcon"
#define ButtonActiveIcon "ButtonActiveIcon"

/* Class record pointer */
extern  WidgetClass  buttonWidgetClass;

/* Widget type definition */
typedef  struct _ButtonRec *ButtonWidget;

#endif /* not FILE_BUTTON_H_SEEN */
