## Process this file with automake to produce Makefile.in
# $Id: Makefile.am,v 1.2 1998/05/20 22:32:56 voss Exp $

bin_PROGRAMS = ylogout
ylogout_SOURCES = Button.c ButtonP.h Button.h \
	pixmapdimen.c pixmapdimen.h \
	ylogout.c
INCLUDES = @X_CFLAGS@
LDADD = @X_LIBS@ @X_PRE_LIBS@ -lXpm -lXmu -lXt -lX11 @X_EXTRA_LIBS@

EXTRA_DIST = active_image.xpm default_image.xpm
