#include <stdlib.h>
#include <gtk/gtk.h>

void close_f (GtkWidget *widget, gpointer *data)
{
		gtk_main_quit();
}

void clicked (GtkWidget *widget, gpointer *data)
{
		g_print("Bouton Clicked\n");
}

int main (int argc, char* argv[])
{
		gtk_init(&argc,&argv);
		GtkWidget* window, *button;

		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window),"WhiteDevil_Prog");
		gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
		gtk_window_set_default_size(GTK_WINDOW(window),300,300);

		button = gtk_button_new_with_label("Coucou c'est moi");
		g_signal_connect(window,"delete-event"
						,G_CALLBACK(gtk_main_quit),NULL);
		gtk_container_add(GTK_CONTAINER(window),button);
		g_signal_connect(GTK_OBJECT(button),"clicked"
						,GTK_SIGNAL_FUNC(clicked),NULL);

		gtk_widget_show(window);
		gtk_widget_show(button);
		gtk_main();
		return 0;
}
