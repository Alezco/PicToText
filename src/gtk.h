#ifndef GTK_H
#define GTK_H

#include <stdlib.h>
#include <gtk/gtk.h>

int main_gtk(int argc, char **argv);
void OnExit(gpointer data);
void OnAbout();
void OnOpen();
void create_file();
void path(GtkWidget *file_selection);

#endif
