/* ylogout.c - a replacement for XLogout
 *
 * Copyright (C) 1998  Jochen Voss.  */

static const  char  rcsid[] = "$Id$";


#include <stdio.h>
#include <stdlib.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xmu/Editres.h>
#include <X11/SM/SMlib.h>

#include "Button.h"


static  XtAppContext  app_con;
static  Widget  toplevel, button;

static  String  fallback_resources [] = {
  "*AllowShellResize: true",
  NULL
};

static  XrmOptionDescRec  options [] = {
  {"-icon", "*Button.icon", XrmoptionSepArg, NULL},
  {"-shape", "*Button.shapeWindow", XrmoptionNoArg, "True"},
  {"+shape", "*Button.shapeWindow", XrmoptionNoArg, "False"}
};


#ifdef __GNUC__
static void die_cb (Widget, XtPointer, XtPointer) __attribute__ ((noreturn));
#endif

static void
die_cb (Widget w, XtPointer client_data, XtPointer call_data)
/* This is the only legal exit point from the program.  */
{
  exit (0);
}

static void 
quit_cb (Widget w, XtPointer client_data, XtPointer call_data)
/* Callback, which is triggered by the button.  If the session manager
 * connection is active send `RequestSaveYourself' to the session
 * manager.  Otherwise just terminate the program.  */
{
  SmcConn  smc_conn;

  XtVaGetValues (toplevel,
		 XtNconnection, &smc_conn,
		 NULL);
  if (smc_conn) {
    SmcRequestSaveYourself (smc_conn, SmSaveBoth, True, SmInteractStyleAny,
			    False, True);
  } else {
    XtAppSetExitFlag (app_con);
  }
}

static void
save_cb (Widget w, XtPointer client_data, XtPointer call_data)
/* This is called by the session manager, when a shutdown is to be
 * performed.  It is followed by either `Die' or `SaveComplete'.  */
{
  XtCheckpointToken  token = (XtCheckpointToken)call_data;

  if (! token->fast) {
    if (token->cancel_shutdown) {
      XtCallActionProc (button, "unset", NULL, NULL, 0);
    } else if (token->shutdown) {
      XtCallActionProc (button, "set", NULL, NULL, 0);
      XtSetSensitive (button, False);
    }
  }
  token->save_success = True;
}

static void
save_complete_cb (Widget w, XtPointer client_data, XtPointer call_data)
/* The shutdown was canceled.  */
{
  XtCallActionProc (button, "unset", NULL, NULL, 0);
  XtSetSensitive (button, True);
}

static void
cancel_cb (Widget w, XtPointer client_data, XtPointer call_data)
/* The shutdown was canceled.  */
{
  XtCallActionProc (button, "unset", NULL, NULL, 0);
  XtSetSensitive (button, True);
}

int
main (int argc, char **argv)
{
  Arg arg[10];
  Cardinal  i;

  toplevel = XtVaOpenApplication (&app_con, "Ylogout",
				  options, XtNumber (options),
				  &argc, argv,
				  fallback_resources, sessionShellWidgetClass,
				  XtNtitle, "Logout",
				  XtNiconName, "Logout",
				  XtVaTypedArg, XtNcurrentDirectory,
				    XtRString, XtCurrentDirectory,
				    strlen(XtCurrentDirectory)+1,
				  NULL);

  XtAddEventHandler (toplevel, NoEventMask, True,
                     _XEditResCheckMessages, NULL);
  
  if (argc != 1) {
    fprintf (stderr, "usage:  %s [+shape] [-icon file.xpm]\n", argv[0]);
    /* do not exit since this is the first program run */
  }
  
  XtAddCallback (toplevel, XtNsaveCallback, save_cb, NULL);
  XtAddCallback (toplevel, XtNdieCallback, die_cb, NULL);
  XtAddCallback (toplevel, XtNcancelCallback, cancel_cb, NULL);
  XtAddCallback (toplevel, XtNsaveCompleteCallback, save_complete_cb, NULL);

  button = XtCreateManagedWidget ("button", buttonWidgetClass, toplevel,
				  NULL, 0);
  XtAddCallback (button, XtNcallback, quit_cb, NULL);

  XtRealizeWidget (toplevel);
  XtAppMainLoop (app_con);

  i = 0;
  XtSetArg (arg[i], XtNjoinSession, False); ++i;
  XtSetValues (toplevel, arg, i);

  die_cb (toplevel, NULL, NULL);
}
