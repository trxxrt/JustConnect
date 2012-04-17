# makefile customisé pour le projet JustConnect

#######################################################

# 1. nom du programme
EXE=JustConnect

# 2. compilateur
CC=gcc

# 3. extension des sources
EXT=c

# 4. choix du répertoire de sources
REP_SRC=src

# 5. choix du répertoire de ressources
REP_RES=res

# 6. flags de compilation
DEP_FLAGS=`pkg-config gtk+-2.0 --libs` `pkg-config --cflags gtk+-2.0`
OPT_FLAGS=-Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Wall -O3

#######################################################

SRC=$(wildcard $(REP_SRC)/*/*/*/*.$(EXT)) $(wildcard $(REP_SRC)/*/*/*.$(EXT)) $(wildcard $(REP_SRC)/*/*.$(EXT)) $(wildcard $(REP_SRC)/*.$(EXT))
OBJ=$(SRC:.$(EXT)=.o)
CFLAGS=$(DEP_FLAGS) $(OPT_FLAGS)

all: $(EXE) clean_obj

allzip: zip zipbin zipsources

zip: clean Release
	rm -f $(EXE).zip
	make clean_obj
	zip -r $(EXE).zip bin/Release/$(EXE) bin/Release/$(REP_RES) $(REP_SRC) $(REP_RES) Makefile
	make clean

zipsources: clean
	rm -f $(EXE)_sources.zip
	zip -r $(EXE)_sources.zip $(REP_SRC) $(REP_RES) Makefile

zipbin: clean all
	rm -f $(EXE)_bin.zip
	zip -r $(EXE)_bin.zip $(EXE) $(REP_RES)
	make clean

Debug: $(EXE)
	mkdir bin || true
	mkdir bin/Debug || true
	cp $(EXE) bin/Debug
	cp -R $(REP_RES) bin/Debug

Release: $(EXE) clean_obj
	mkdir bin || true
	mkdir bin/Release || true
	cp $(EXE) bin/Release
	cp -R $(REP_RES) bin/Release

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
	find . -name "*.temp" -exec rm -f {} \;
	rm -Rf bin

clean_zip:
	rm -f $(EXE).zip
	rm -f $(EXE)_bin.zip
	rm -f $(EXE)_sources.zip
	
clean_obj:
	@echo "\n=== Clean up du projet ===\n"
	rm -f $(OBJ)
	@echo "done.\n"