CC = clang
CFLAGS = -Wall -Wextra -Werror -O2 -std=c99
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
SRC = src/detect.c src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) $(GTK_CFLAGS) -o PicToText
clean: 
	rm -rf *.o
