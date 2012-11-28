MAINTAINERCLEANFILES = Makefile.in
SUBDIRS = images 

EDJE_CC = @edje_cc@
EDJE_FLAGS = \
	-v \
	-id $(top_srcdir)/data/themes/$(NAME)/images \
	-fd $(top_srcdir)/data/themes/$(NAME)/fonts \
	@EDJE_DEF@

filesdir = $(pkgdatadir)/themes
files_DATA = debuglauncher_check.edj

EXTRA_DIST = check.edc 

debuglauncher_check.edj: Makefile debuglauncher_check.edc
	$(EDJE_CC) $(EDJE_FLAGS) \
	$(top_srcdir)/data/themes/debuglauncher_check.edc \
	$(top_builddir)/data/themes/debuglauncher_check.edj

clean-local:
	rm -f *.edj

