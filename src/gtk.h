#ifndef GTK_H
#define GTK_H

#include <stdlib.h>
#include <gtk/gtk.h>

int main_gtk(int argc, char *argv[]);
int open_dialog(gpointer window, gpointer pVbox);
void Quit(gpointer data);


#endif
