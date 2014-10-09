PicToText : main.c load_image.c GTK_test.c
CC = clang
CFLAGS = -Wall -Wextra -Werror -O2 -std=c99
GTK_CFLAGS = $(pkg-config --libs --cflags gtk+-2.0)
SRC = main.c

all:
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(SRC) -o PicToText
clean: 
	rm -rf *.o
