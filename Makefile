CC = clang
CPPFLAGS = `pkg-config --cflags sdl`
LDLIBS = `pkg-config --libs sdl` -lSDL_image
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS = -Wall -Wextra -Werror -O2 -std=c99 -g
SRC = src/gtk.c src/detect.c src/neuralnetwork.c src/main.c

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) $(GTK_CFLAGS)$(LDLIBS) -lm -o PicToText
clean: 
	rm -rf *.o
