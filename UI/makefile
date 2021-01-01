gresource.c:gresource.xml *.glade
	glib-compile-resources --generate-source $<

gresource.h:gresource.xml *.glade
	glib-compile-resources --generate-header $<

all:gresource.h gresource.c
	@echo "Generate Gresources\n"
