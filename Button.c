/* Button.c - Implementation of the Button widget
 *
 * Copyright (C) 1998  Jochen Voss.  */

static const  char  rcsid[] = "$Id$";

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/extensions/shape.h>
#include <X11/xpm.h>

#include "pixmapdimen.h"
#include "ButtonP.h"

/**********************************************************************
 * Resource management - This section defines the resources introduced
 *			 by the Button widget class.
 */

static XtResource resources[] = {
  {XtNicon, XtCIcon, XtRIcon, sizeof(struct icon),
   XtOffset(ButtonWidget, button.icon),
   XtRString, ButtonDefaultIcon },
  {XtNactiveIcon, XtCIcon, XtRIcon, sizeof(struct icon),
   XtOffset(ButtonWidget, button.active_icon),
   XtRString, ButtonActiveIcon },
  {XtNcallback, XtCCallback, XtRCallback, sizeof(XtCallbackList), 
   XtOffset(ButtonWidget, button.callbacks),
   XtRCallback, (XtPointer)NULL},
  {XtNshapeWindow, XtCShapeWindow, XtRBoolean, sizeof (Boolean),
   XtOffset(ButtonWidget, button.shape_window),
   XtRImmediate, (XtPointer)True}
};

static  struct icon  cvt_icon_return;

#include "default_image.xpm"
#include "active_image.xpm"

static Boolean
ButtonCvtStringToIcon(Display* dpy, XrmValue *args, Cardinal *num_args,
		      XrmValue *fromVal, XrmValue *toVal,
		      XtPointer *converter_data)
/* Convert a string into an icon.  This takes a screen as a converter
 * argument.  */
{
  Screen *screen;
  char *name;
  struct icon  icon;
  int res;

  if (*num_args != 1) {
    XtAppWarningMsg (XtDisplayToApplicationContext(dpy),
		     "wrongParameters", "cvtStringToIcon", "ButtonError",
		     "String to Icon conversion requires a screen argument",
		     (String *) NULL,
		     (Cardinal *)NULL);
    return  False;
  }

  if (toVal->addr != NULL && toVal->size < sizeof(struct icon)) {
    toVal->size = sizeof (struct icon);
    return False;
  }

  screen = *((Screen **) args[0].addr);
  name = (char *)fromVal->addr;

  if (strcasecmp (name, ButtonDefaultIcon) == 0) {
    res = XpmCreatePixmapFromData (DisplayOfScreen (screen),
				   RootWindowOfScreen (screen),
				   default_image_xpm,
				   &icon.foreground, &icon.mask, NULL);
  } else if (strcasecmp (name, ButtonActiveIcon) == 0) {
    res = XpmCreatePixmapFromData (DisplayOfScreen (screen),
				   RootWindowOfScreen (screen),
				   active_image_xpm,
				   &icon.foreground, &icon.mask, NULL);
  } else {
    res = XpmReadFileToPixmap (DisplayOfScreen (screen),
			       RootWindowOfScreen (screen),
			       name, &icon.foreground, &icon.mask, NULL);
  }

  if (res<0) {
    Cardinal  num_args = 2;
    String  args[num_args];
    
    args[0] = name;
    args[1] = XpmGetErrorString (res);
    XtAppWarningMsg (XtDisplayToApplicationContext(dpy),
		     "loadError",
		     "loadIcons", "ButtonWarning",
		     "\"%s\": %s",
		     args, &num_args);
    XtStringConversionWarning((String)fromVal->addr, "Icon");
    return  False;
  }
  
  if (toVal->addr != NULL) {
    /* We checked `toVal->size >= sizeof (struct icon)'
     * at the beginning of the function.  */
    *(struct icon *)(toVal->addr) = icon;
  } else {
    cvt_icon_return = icon;
    toVal->addr = (XPointer)&cvt_icon_return;
  }
  toVal->size = sizeof (struct icon);
  return  True;
}

static void
FreeIcon (XtAppContext app, XrmValue *toVal, XtPointer converter_data,
	     XrmValue *args, Cardinal *num_args)
/* Free the memory allocated by an icon.  */
{
  Screen *screen;
  Display *dpy;
  struct icon  icon;

  if (*num_args != 1) {
    XtAppErrorMsg (app, "wrongParameters", "freeIcon", "ButtonError",
		   "Freeing an icon needs a screen argument",
		   (String *) NULL, (Cardinal *)NULL);
    return;
  }

  screen = *((Screen **) args[0].addr);
  dpy = DisplayOfScreen (screen);
  icon = *(struct icon*)toVal->addr;

  XFreePixmap (dpy, icon.foreground);
  XFreePixmap (dpy, icon.mask);
}

static XtConvertArgRec  iconConvertArgs[] = {
  { XtWidgetBaseOffset, (XtPointer)XtOffset (Widget, core.screen),
    sizeof(Screen *) }
};

/**********************************************************************
 * `CoreClassPart' methods.
 */

static void
ClassInitialize (void)
{
  XtSetTypeConverter (XtRString, XtRIcon, ButtonCvtStringToIcon,
		      iconConvertArgs, XtNumber(iconConvertArgs),
		      XtCacheByDisplay, FreeIcon);
}

static void
Initialize (Widget request, Widget new, ArgList args, Cardinal *num_args)
{
  ButtonWidget ww = (ButtonWidget) new;
  ButtonPart *part = &(ww->button);
  Display *dpy = XtDisplay (new);
  unsigned  width1, height1, width2, height2;

  get_pixmap_dimensions (dpy, part->icon.foreground, &width1, &height1);
  get_pixmap_dimensions (dpy, part->active_icon.foreground, &width2, &height2);
  if (ww->core.width == 0) {
    ww->core.width = width1 > width2 ? width1 : width2;
    if (ww->core.width == 0)  ww->core.width = 10;
    part->auto_width = True;
  } else {
    part->auto_width = False;
  }
  if (ww->core.height == 0) {
    ww->core.height = height1 > height2 ? height1 : height2;
    if (ww->core.height == 0)  ww->core.height = 10;
    part->auto_height = True;
  } else {
    part->auto_height = False;
  }

  part->normal_x = (ww->core.width - width1)/2;
  part->normal_y = (ww->core.height - height1)/2;
  part->active_x = (ww->core.width - width2)/2;
  part->active_y = (ww->core.height - height2)/2;
  
  part->gc
    = XtAllocateGC (new, 0, 0, NULL, 0,
		    GCForeground|GCBackground|GCLineWidth|GCLineStyle
		      |GCCapStyle|GCJoinStyle|GCFillStyle|GCFillRule|GCArcMode
		      |GCTile|GCStipple|GCTileStipXOrigin|GCTileStipYOrigin
		      |GCFont|GCDashOffset|GCDashList);
  part->set = False;
  if (part->shape_window)  part->update_shape = True;
}

static void
Destroy (Widget w)
{
  ButtonWidget ww = (ButtonWidget) w;
  ButtonPart *part = &(ww->button);

  XtReleaseGC (w, part->gc);
}

static void
set_window_shape (ButtonWidget ww)
{
  ButtonPart *part = &(ww->button);
  Widget parent;
  int x, y;

  x = part->set ? part->active_x : part->normal_x;
  y = part->set ? part->active_y : part->normal_y;
  for (parent = (Widget)ww; XtParent(parent); parent = XtParent (parent)) {
    x += parent->core.x + parent->core.border_width;
    x += parent->core.y + parent->core.border_width;
  }
  XShapeCombineMask (XtDisplay (parent), XtWindow (parent), ShapeBounding,
		     x, y,
		     part->set ? part->active_icon.mask : part->icon.mask,
		     ShapeSet);
  part->update_shape = False;
}

static void
clear_window_shape (ButtonWidget ww)
{
  ButtonPart *part = &(ww->button);
  Widget parent = (Widget)ww;

  while (XtParent(parent))  parent = XtParent (parent);
  XShapeCombineMask (XtDisplay (parent), XtWindow (parent), ShapeBounding,
		     0, 0, None, ShapeSet);
  part->update_shape = False;
}

static void
Redisplay (Widget w, XEvent *event, Region region)
/* Redraw an exposed part of the Button widget.  */
{
  if (XtIsRealized (w)) {
    ButtonWidget ww = (ButtonWidget) w;
    ButtonPart *part = &(ww->button);
    Display *dpy = XtDisplay (w);

    if (ww->button.update_shape)  set_window_shape (ww);

    if (! part->set) {
      XCopyArea (dpy, part->icon.foreground, XtWindow(w), part->gc,
		 0, 0, ww->core.width, ww->core.height,
		 part->normal_x, part->normal_y);
    } else {
      XCopyArea (dpy, part->active_icon.foreground, XtWindow(w), part->gc,
		 0, 0, ww->core.width, ww->core.height,
		 part->active_x, part->active_y);
    }
  }
}

static Boolean
SetValues (Widget current, Widget request, Widget new,
	   ArgList args, Cardinal *num_args)
{
  ButtonWidget ww = (ButtonWidget) new;
  ButtonWidget ww_old = (ButtonWidget) current;
  Display *dpy = XtDisplay (new);
  Boolean  redisplay = False;

  if (ww->button.icon.mask != ww_old->button.icon.mask
      || ww->button.active_icon.mask != ww_old->button.active_icon.mask) {
    unsigned  width1, height1, width2, height2;
    
    get_pixmap_dimensions (dpy, ww->button.icon.foreground, &width1, &height1);
    get_pixmap_dimensions (dpy, ww->button.active_icon.foreground,
			   &width2, &height2);
    if (((ButtonWidget)request)->core.width == 0)
      ww->button.auto_width = True;
    if (ww->button.auto_width) {
      ww->core.width = width1 > width2 ? width1 : width2;
      if (ww->core.width == 0)  ww->core.width = 10;
    }
    if (((ButtonWidget)request)->core.height == 0)
      ww->button.auto_height = True;
    if (ww->button.auto_height) {
      ww->core.height = height1 > height2 ? height1 : height2;
      if (ww->core.height == 0)  ww->core.height = 10;
    }
    ww->button.normal_x = (ww->core.width - width1)/2;
    ww->button.normal_y = (ww->core.height - height1)/2;
    ww->button.active_x = (ww->core.width - width2)/2;
    ww->button.active_y = (ww->core.height - height2)/2;
    if (ww->button.shape_window)  ww->button.update_shape = True;
    redisplay = True;
  }

  if (ww->button.shape_window != ww_old->button.shape_window) {
    if (ww->button.shape_window) {
      ww->button.update_shape = True;
      redisplay = True;
    } else {
      if (XtIsRealized (new))  clear_window_shape (ww);
      ww->button.update_shape = False;
    }
  }

  return  redisplay;
}

/**********************************************************************
 * Button actions.
 */

static void
notify_action (Widget w, XEvent *event, String *params, Cardinal *num_params)
{
  ButtonWidget ww = (ButtonWidget) w;

  if (ww->button.set) {
    XtCallCallbackList (w, ww->button.callbacks, NULL);
  }
}

static void
set_action (Widget w, XEvent *event, String *params, Cardinal *num_params)
{
  ButtonWidget ww = (ButtonWidget) w;

  if (ww->button.set)  return;
  ww->button.set = True;
  if (ww->button.shape_window)  ww->button.update_shape = True;
  if (XtIsRealized (w))
    XClearArea (XtDisplay(w), XtWindow(w), 0, 0, 0, 0, True);
}

static void
unset_action (Widget w, XEvent *event, String *params, Cardinal *num_params)
{
  ButtonWidget ww = (ButtonWidget) w;

  if (! ww->button.set)  return;
  ww->button.set = False;
  if (ww->button.shape_window)  ww->button.update_shape = True;
  if (XtIsRealized (w))
    XClearArea (XtDisplay(w), XtWindow(w), 0, 0, 0, 0, True);
}

static XtActionsRec actions[] = {
  { "notify", notify_action },
  { "set", set_action },
  { "unset", unset_action }
};

static  char  default_translations[] = "\
<LeaveWindow>: unset()\n\
<Btn1Down>: set()\n\
<Btn1Up>: notify() unset()";

/**********************************************************************
 * The unique class record of the Button widget class.
 */

ButtonClassRec buttonClassRec = {
  { /* core_class */
    (WidgetClass)&widgetClassRec, /* superclass */
    "Button",			/* class_name */
    sizeof (ButtonRec),		/* widget_size */
    ClassInitialize,		/* class_initialize */
    NULL,			/* class_part_initialize */
    False,			/* class_inited */
    Initialize,			/* initialize */
    NULL,			/* initialize_hook (obsolete) */
    XtInheritRealize,		/* realize */
    actions,			/* actions */
    XtNumber (actions),		/* num_actions */
    resources,			/* resources */
    XtNumber(resources),	/* num_resources */
    NULLQUARK,			/* xrm_class */
    True,			/* compress_motion */
    True,			/* compress_exposure */
    True,			/* compress_enterleave */
    False,			/* visible_interest */
    Destroy,			/* destroy */
    XtInheritResize,		/* resize */
    Redisplay,			/* expose */
    SetValues,			/* set_values */
    NULL,			/* set_values_hook */
    XtInheritSetValuesAlmost,	/* set_values_almost */
    NULL,			/* get_values_hook */
    XtInheritAcceptFocus,	/* accept_focus */
    XtVersion,			/* version */
    NULL,			/* callback_private */
    default_translations,	/* tm_table */
    XtInheritQueryGeometry,	/* query_geometry */
    XtInheritDisplayAccelerator, /* display_accelerator */
    NULL			/* extension */
  },
  { /* button_class */
    NULL			/* extension */
  }
};

/* Class record pointer */
WidgetClass  buttonWidgetClass = (WidgetClass)&buttonClassRec;
