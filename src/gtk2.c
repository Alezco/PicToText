#include "gtk.h"
#include "neuralnetwork.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "detect.h"
#include <string.h>

GtkWidget *pHBox, *view;
char *image_path;
char a;

void open_dialog(gpointer *widget,gpointer window, gpointer pVbox)
{
	GtkWidget *dialog, *image;
	//*pHbox;
	image = NULL;
	//pHbox = NULL;
	widget = NULL;
	dialog = gtk_file_chooser_dialog_new("Chemin d'accès",
					GTK_WINDOW(window),
					GTK_FILE_CHOOSER_ACTION_OPEN,
					GTK_STOCK_OK,
					GTK_RESPONSE_OK,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_CANCEL,
					NULL);

	gtk_widget_show_all(dialog);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
				g_get_home_dir());
	gint resp = gtk_dialog_run(GTK_DIALOG(dialog));

	if (resp == GTK_RESPONSE_OK)
	{
		gtk_widget_destroy(pHBox);
		gchar* path;
		pHBox = gtk_hbox_new(FALSE,8);
		view = gtk_text_view_new();
		gtk_widget_set_size_request(view,800,300);
		path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

		//path = gtk_file_selection_get_filename(GTK_FILE_CHOOSER(dialog));
		char *filename;
     
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		image_path = filename;
		g_print("%s ouvert\n", path);
		//image_path = path; 
		//str = strcat(str, (char*)path);
		/*printf(" test %s", (char *)image_path);
		src = strcat(src,  (char *)image_path);
		image_path = src;*/
		//label = gtk_label_new("PicToTest zone de texte editable");
		image = gtk_image_new_from_file(path);
		//path = gtk_file_selection_get_filename(image);
		//gtk_box_pack_start(GTK_BOX(pHBox),label,FALSE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(pHBox),image,FALSE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(pHBox),view,FALSE,TRUE,0);
		gtk_container_add(GTK_CONTAINER(pVbox),pHBox);
		gtk_widget_show_all(pVbox);
		g_free(path);
		gtk_widget_destroy(dialog);
	}
	else
		{
			g_print("Canceled\n");
			gtk_widget_destroy(dialog);
		}
}
void process()
{
  printf("action\n");
  printf("%s", image_path);
  start(image_path, a);
  GtkWidget *image, *pHbox, *window;
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
  gtk_container_set_border_width(GTK_CONTAINER(window),10);

  pHbox = gtk_hbox_new(FALSE,8);
  image = gtk_image_new_from_file("sortie");
  gtk_box_pack_start(GTK_BOX(pHbox), image, FALSE,TRUE,0);
  //gtk_box_pack_start(GTK_BOX(pHbox),view,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window), pHbox);
  //gtk_container_add(GTK_CONTAINER(pHbox), image);
  gtk_widget_show_all(window);
}
void Quit(gpointer data)
{
	GtkWidget *pQuestion;

	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_YES_NO,
				"Voulez vous quitter PicToText?");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
		{
			case GTK_RESPONSE_YES:
				gtk_main_quit();
				break;
			case GTK_RESPONSE_NONE:
			case GTK_RESPONSE_NO:
				gtk_widget_destroy(pQuestion);
				break;
		}
}

int main_gtk(int argc, char *argv[])
{

  //initialisation var
  if (argc > 1)
    {
      a = *argv[1];
    }
  else
    {
      a = 'b';
    }
      
	/* GtkWidget is the storage type for widgets */
	GtkWidget *window;
	GtkWidget *pVBox, *fixed;
	GtkWidget *button;
	GtkWidget *button2;
	GtkWidget *button3;

	/* Initialise GTK */
	gtk_init(&argc, &argv);
	fixed = gtk_fixed_new();
	view = gtk_text_view_new();
	pHBox = gtk_hbox_new(FALSE,8);

	/* Create a new window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
	gtk_window_set_title(GTK_WINDOW(window), "PicToText");

	gtk_container_set_border_width(GTK_CONTAINER(window),5);

	/* Here we connect the "destroy" event to a signal handler */ 
	gtk_signal_connect (GTK_OBJECT (window), "destroy",
					GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

	/* Sets the border width of the window. */
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	/* Create a pVertical Box */
	pVBox = gtk_vbox_new(FALSE,1);
	gtk_container_add(GTK_CONTAINER(window), pVBox);
	gtk_widget_set_size_request(pVBox, 100,35);

	button = gtk_button_new_with_label ("Ouvrir");
	gtk_box_pack_start(GTK_BOX(pVBox),fixed,FALSE,FALSE,0);

	//gtk_box_pack_start(GTK_BOX(pVBox),button, FALSE,FALSE,0);
	gtk_fixed_put(GTK_FIXED(fixed), button,550,10);
	gtk_widget_set_size_request(button,100,30);

	button2 = gtk_button_new_with_label ("Convertir");
	gtk_fixed_put(GTK_FIXED(fixed),button2,650,10);
	gtk_widget_set_size_request(button2,100,30);
	//gtk_box_pack_start(GTK_BOX(pVBox),button2,FALSE,FALSE,0);

	button3 = gtk_button_new_with_label("Quitter");
	gtk_fixed_put(GTK_FIXED(fixed),button3,750,10);
	gtk_widget_set_size_request(button3,100,30);
	//gtk_box_pack_start(GTK_BOX(pVBox),button3,FALSE,FALSE,0);
	
	gtk_signal_connect(GTK_OBJECT(button),"clicked",
					GTK_SIGNAL_FUNC(open_dialog),
					GTK_OBJECT(pVBox));
	gtk_signal_connect_object(GTK_OBJECT(button3),"clicked",
					GTK_SIGNAL_FUNC(Quit),
					GTK_OBJECT(window));
	gtk_signal_connect_object(GTK_OBJECT(button2),"clicked",
				  GTK_SIGNAL_FUNC(process),
				  GTK_OBJECT(window));
	/* Display the window */
	gtk_widget_show_all (window);
	/* Enter the event loop */
	gtk_main ();
	return(0);
}
