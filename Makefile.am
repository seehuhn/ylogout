## Process this file with automake to produce Makefile.in

bin_PROGRAMS = ylogout
ylogout_SOURCES = Button.c ButtonP.h Button.h \
	pixmapdimen.c pixmapdimen.h \
	ylogout.c
INCLUDES = @X_CFLAGS@
LDADD = @X_LIBS@ @X_PRE_LIBS@ -lXpm -lXmu -lXext -lXt -lX11 @X_EXTRA_LIBS@

EXTRA_DIST = active_image.xpm default_image.xpm
