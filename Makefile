# makefile customisé pour le projet JustConnect

# 1. nom du programme
EXE=JustConnect

# 2. flags de compilation allegro
FLAGS=`pkg-config gtk+-2.0 --libs` `pkg-config --cflags gtk+-2.0` -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wall -g -O3

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

Debug: $(EXE)
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
