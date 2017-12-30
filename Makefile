
CPPFLAGS=$(shell sdl2-config --cflags)$(EXTRA_CPPFLAGS)
LDLIBS=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf $(EXTRA_LDLIBS)

PKG_CONFIG?=pkg-config
BINARY?=main

all: $(BINARY)
$(BINARY): config.o texture.o entity.o entity-controller.o player-controller.o
clean:
	rm -f *.o $(BINARY)
gitignore:
	echo "**/*.o\n$(BINARY)" > .gitignore
.PHONY: all clean gitignore
