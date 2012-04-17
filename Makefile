# makefile customisé pour le projet JustConnect

# 1. nom du programme
EXE=JustConnect

# 2. compilateur
CC=gcc

# 3. extension des sources
EXT=c

# 4. flags de compilation allegro
DEP_FLAGS=`pkg-config gtk+-2.0 --libs` `pkg-config --cflags gtk+-2.0`
OPT_FLAGS=-Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wall -O3
CFLAGS=$(DEP_FLAGS) $(OPT_FLAGS)

# 5. liste des fichiers à compiler
SRC=$(wildcard src/*/*.$(EXT)) $(wildcard src/*.$(EXT))

# 6. liste des fichiers objets à linker
OBJ=$(SRC:.$(EXT)=.o)

###################################################

all: $(EXE) clean_obj

allzip: zip zipbin zipsources

zip: clean Release
	rm -f $(EXE).zip
	make clean_obj
	zip -r $(EXE).zip bin/Release/$(EXE) bin/Release/res src res Makefile
	make clean

zipsources: clean
	rm -f $(EXE)_sources.zip
	zip -r $(EXE)_sources.zip src res Makefile

zipbin: clean Release
	rm -f $(EXE)_bin.zip
	zip -r $(EXE)_bin.zip $(EXE) res
	make clean

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

%.o: %.$(EXT) %.h
	@echo "\n > compilation de $<"
	$(CC) $(CFLAGS) -o $@ -c $<

cleanDebug: clean_all

cleanRelease: clean_all

clean_all: clean_zip clean

clean: clean_obj clean_cdb
	rm -f $(EXE)

clean_cdb:
	rm -f $(EXE).layout $(EXE).depend
	find . -name "*.bak" -exec rm -f {} \;
	rm -Rf bin

clean_zip:
	rm -f $(EXE).zip
	rm -f $(EXE)_bin.zip
	rm -f $(EXE)_sources.zip
	
clean_obj:
	@echo "\n=== Clean up du projet ===\n"
	rm -f $(OBJ)
	@echo "done.\n"