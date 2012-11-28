## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src data

debuglauncherdocdir = ${prefix}/doc/debuglauncher
debuglauncherdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = $(debuglauncherdoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(debuglauncherdocdir)
