## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	$(OILAUNCH_CFLAGS) \
	$(LIBXML___CFLAGS) \
	$(LOG4CXX_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = debuglauncher

debuglauncher_SOURCES =  \
	Main.cpp \
	Main.h \
	SettingsWindow.cpp \
	SettingsWindow.h \
	XMLLoader.cpp \
	XMLLoader.h \
	Logger.h \
	searchFile.cpp \
	searchFile.h \
	Exceptions.h \
	Exceptions.cpp \
	Preferences.cpp \
	Preferences.h \
	XMLWriter.cpp \
	XMLWriter.h

debuglauncher_LDFLAGS = 

debuglauncher_LDADD = $(OILAUNCH_LIBS) \
		      $(LIBXML___LIBS) \
		      $(LOG4CXX_LIBS)

