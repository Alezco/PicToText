CC = clang
CPPFLAGS = `pkg-config --cflags sdl`
LDLIBS = `pkg-config --libs sdl` -lSDL_image
CFLAGS = -Wall -Wextra -Werror -O2 -std=c99
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
SRC = src/neuralnetwork.c src/main.c

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(SRC) $(GTK_CFLAGS) -lm -o PicToText
clean: 
	rm -rf *.o
