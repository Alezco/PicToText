#ifndef GTK_H
#define GTK_H

#include <stdlib.h>
#include <gtk/gtk.h>

int main_gtk(int argc, char *argv[]);
void open_dialog(gpointer *widget,gpointer window, gpointer pVbox);
void Quit(gpointer data);


#endif
