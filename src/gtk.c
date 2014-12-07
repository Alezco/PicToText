#include "gtk.h"
#include "neuralnetwork.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "detect.h"
#include "traitement.h"

GtkWidget *pHBox, *text;
gchar *chemin;
char a;
#define TAILLE_MAX 1000


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
		text = gtk_entry_new_with_max_length(5000);
		gtk_entry_set_text(GTK_ENTRY(text),"hello");
		gtk_widget_show(text);
		gtk_widget_set_size_request(text,800,300);
		path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		g_print("%s ouvert\n", path);
		chemin = path;
		//label = gtk_label_new("PicToTest zone de texte editable");
		image = gtk_image_new_from_file(path);
		//gtk_box_pack_start(GTK_BOX(pHBox),label,FALSE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(pHBox),image,FALSE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(pHBox),text,FALSE,TRUE,0);
		gtk_container_add(GTK_CONTAINER(pVbox),pHBox);
		gtk_widget_show_all(pVbox);
		//g_free(path);
		gtk_widget_destroy(dialog);
	}
	else
		{
			g_print("Canceled\n");
			gtk_widget_destroy(dialog);
		}
}
void bruit()
{
   g_print("reduction du bruit\n");

   float gauss[][3] = {
  {1, 1, 1},
  {1, 2, 1},
  {1, 1, 1}
};


   SDL_Surface *ecran = NULL, *surface_tmp_c = NULL;
    SDL_Rect position;

    position.x = 0;
    position.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    surface_tmp_c = IMG_Load(chemin);

    ecran = SDL_SetVideoMode(surface_tmp_c->w, surface_tmp_c->h, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("PicToText", NULL);

    //IMPORTANT
    convolution(surface_tmp_c, 3, gauss);
    SDL_SaveBMP(surface_tmp_c, "image_convolution");
    //IMPORTANT

    SDL_Flip(ecran);

    SDL_FreeSurface(surface_tmp_c);
    SDL_Quit();

    GtkWidget *image, *pHbox, *window;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
  gtk_container_set_border_width(GTK_CONTAINER(window),10);

  pHbox = gtk_hbox_new(FALSE,8);
  image = gtk_image_new_from_file("image_convolution");
  gtk_box_pack_start(GTK_BOX(pHbox), image, FALSE,TRUE,0);
  //gtk_box_pack_start(GTK_BOX(pHbox),view,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window), pHbox);
  //gtk_container_add(GTK_CONTAINER(pHbox), image);
  gtk_widget_show_all(window);
}

void binarise()
{
   g_print("binarise\n");
   SDL_Surface *ecran = NULL, *surface_tmp = NULL;
    SDL_Rect position;

    position.x = 0;
    position.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    surface_tmp = IMG_Load(chemin);

    ecran = SDL_SetVideoMode(surface_tmp->w, surface_tmp->h, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("PicToText", NULL);

    //IMPORTANT
    binaire(surface_tmp);
    SDL_SaveBMP(surface_tmp, "image_binariser");
    //IMPORTANT

    SDL_Flip(ecran);

    SDL_FreeSurface(surface_tmp);
    SDL_Quit();

    GtkWidget *image, *pHbox, *window;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
  gtk_container_set_border_width(GTK_CONTAINER(window),10);

  pHbox = gtk_hbox_new(FALSE,8);
  image = gtk_image_new_from_file("image_binariser");
  gtk_box_pack_start(GTK_BOX(pHbox), image, FALSE,TRUE,0);
  //gtk_box_pack_start(GTK_BOX(pHbox),view,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window), pHbox);
  //gtk_container_add(GTK_CONTAINER(pHbox), image);
  gtk_widget_show_all(window);
}
void greyscale()
{
  g_print("greyscale\n");
  SDL_Surface *ecran = NULL, *surface_tmp_g = NULL;
    SDL_Rect position;

    position.x = 0;
    position.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    surface_tmp_g = IMG_Load(chemin);

    ecran = SDL_SetVideoMode(surface_tmp_g->w, surface_tmp_g->h, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("PicToText", NULL);

    //IMPORTANT
    grey(surface_tmp_g);
    SDL_SaveBMP(surface_tmp_g, "image_grey");
    //IMPORTANT

    SDL_Flip(ecran);

    SDL_FreeSurface(surface_tmp_g);
    SDL_Quit();

    GtkWidget *image, *pHbox, *window;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
  gtk_container_set_border_width(GTK_CONTAINER(window),10);

  pHbox = gtk_hbox_new(FALSE,8);
  image = gtk_image_new_from_file("image_grey");
  gtk_box_pack_start(GTK_BOX(pHbox), image, FALSE,TRUE,0);
  //gtk_box_pack_start(GTK_BOX(pHbox),view,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(window), pHbox);
  //gtk_container_add(GTK_CONTAINER(pHbox), image);
  gtk_widget_show_all(window);
}

void process()
{
  start(chemin, a);
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

  //////////////////////////////////////////////////////////////
  FILE *file_texte = NULL;

  file_texte = fopen("save/texte.txt", "r"); 

char c[TAILLE_MAX] = "";

if(file_texte != NULL)
 { 
    fgets(c, TAILLE_MAX, file_texte);
 }

fclose(file_texte);


//////////////////////////////////////////////////////////////////
  gtk_entry_set_text(GTK_ENTRY(text),c);
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
	GtkWidget *img;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *check1, *check2, *check3;

	/* Initialise GTK */
	gtk_init(&argc, &argv);
	fixed = gtk_fixed_new();
	text = gtk_text_view_new();
	pHBox = gtk_hbox_new(FALSE,8);
	img = gtk_image_new_from_file("image/logo_telechargement.png");

	/* Create a new window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),1550,900);
	gtk_window_set_title(GTK_WINDOW(window), "PicToText");

	check1 = gtk_check_button_new_with_label("niveau de gris");
	check2= gtk_check_button_new_with_label("réduction du bruit");
	check3 = gtk_check_button_new_with_label("binariser");

	gtk_fixed_put(GTK_FIXED(fixed), check1, 480,50);
	gtk_fixed_put(GTK_FIXED(fixed),check2,650,50);
	gtk_fixed_put(GTK_FIXED(fixed), check3, 830,50);
	gtk_fixed_put(GTK_FIXED(fixed), img, 80,0);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1),FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2),FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check3),FALSE);

	GTK_WIDGET_UNSET_FLAGS(check1, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS(check2, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS(check3, GTK_CAN_FOCUS);

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

	/*
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check2)))
		bruit();
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check3)))
		binarise();
	*/
	
	g_signal_connect(check1,"clicked",
					G_CALLBACK(greyscale), (gpointer) window);
	g_signal_connect(check2,"clicked",
					G_CALLBACK(bruit),(gpointer) window);
	g_signal_connect(check3,"clicked",
					G_CALLBACK(binarise),(gpointer) window);
	
	/* Display the window */
	gtk_widget_show_all (window);
	/* Enter the event loop */
	gtk_main ();
	return(0);
}
