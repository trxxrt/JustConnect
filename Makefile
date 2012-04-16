# makefile customisé pour le projet JustConnect

# 1. nom du programme
EXE=JustConnect

# 2. compilateur
CC=gcc

# 2. flags de compilation allegro
DEP_FLAGS=`pkg-config gtk+-2.0 --libs` `pkg-config --cflags gtk+-2.0`
OPT_FLAGS=-Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wall -g -O3
CFLAGS=$(DEP_FLAGS) $(OPT_FLAGS)

# 3. liste des fichiers à compiler
SRC=$(wildcard src/*/*.c) $(wildcard src/*.c)

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
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "done.\n"

%.o: %.c %.h
	@echo "\n > compilation de $<"
	$(CC) $(CFLAGS) -o $@ -c $<

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
