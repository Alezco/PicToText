PicToText : main.c load_image.c
	clang -o PicToText main.c load_image.c -Wall -Wextra -Werror -std=c99 `pkg-config --cflags --libs gtk+2.0`

clean :
	rm -rf *.o
