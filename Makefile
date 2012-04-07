# makefile customisé pour le projet JustConnect

# 1. nom du programme
EXE=JustConnect

# 2. flags de compilation allegro
FLAGS=`pkg-config gtk+-2.0 --libs` -pthread -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wall -g -O3

# 3. liste des fichiers à compiler
SHARED=$(wildcard src/shared/*.c)
MODEL=$(wildcard src/model/*.c)
VIEW=$(wildcard src/view/*.c)
CONTROLLER=$(wildcard src/controller/*.c)
ROOT=$(wildcard src/*.c)
SRC=$(SHARED) $(MODEL) $(VIEW) $(CONTROLLER) $(ROOT)

# 4. liste des fichiers objets à linker
OBJ=$(SRC:.c=.o)

###################################################

all: $(EXE) clean_obj

Debug: $(EXE) clean_obj
	mkdir bin || true
	mkdir bin/Debug || true
	cp $(EXE) bin/Debug
	cp -R res bin/Debug

Release: $(EXE) clean_obj
	mkdir bin || true
	mkdir bin/Release || true
	cp $(EXE) bin/Release
	cp -R res bin/Release

$(EXE): $(OBJ)
	@echo "\n=== linking des objets ===\n"
	gcc -o $@ $^ $(FLAGS)
	@echo "done.\n"

%.o: %.c %.h
	@echo "\n > compilation de $<"
	gcc -o $@ -c $< $(FLAGS)

cleanDebug: clean

cleanRelease: clean

clean: clean_obj
	rm -f $(EXE)
	rm -f JustConnect.layout JustConnect.depend
	rm -Rf bin
	
clean_obj:
	@echo "\n=== Clean up du projet ===\n"
	rm -f $(OBJ)
	@echo "done.\n"
