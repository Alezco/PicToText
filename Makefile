CC = clang
CPPFLAGS = `pkg-config --cflags sdl`
LDLIBS = `pkg-config --libs sdl` -lSDL_image
CFLAGS = -Wall -Wextra -Werror -O2 -std=c99
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
SRC = src/main.c

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(SRC) $(GTK_CFLAGS) -o PicToText
clean: 
	rm -rf *.o
