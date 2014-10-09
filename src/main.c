#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "detect.h"

int main(int argc, char *argv[])
{
	Printlol();
	gtk_init(&argc, &argv);
	GtkWidget* window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),300,300);
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
