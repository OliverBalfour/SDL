
CPPFLAGS=$(shell sdl2-config --cflags)$(EXTRA_CPPFLAGS)
LDLIBS=$(shell sdl2-config --libs) $(EXTRA_LDLIBS)

PKG_CONFIG?=pkg-config
BINARY?=main

all: $(BINARY)
$(BINARY): config.o
clean:
	rm -f *.o $(BINARY)
gitignore:
	echo "**/*.o\n$(BINARY)" > .gitignore
.PHONY: all clean gitignore
