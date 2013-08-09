/* Button.h - Public Button widget declaration
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
