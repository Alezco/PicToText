#include "gtk.h"

/* Définition des éléments du menu */
static GtkItemFactoryEntry MenuItem[] =
{

	{ "/_File", NULL, NULL, 0, "<Branch>", NULL },
	{ "/File/_Open",NULL,OnOpen, 0, "<StockItem>", GTK_STOCK_OPEN },
	{ "/File/_Save", NULL, NULL, 0, "<StockItem>", GTK_STOCK_SAVE },
	{"/File/_Close", "<ctrl>X",NULL,0, "<StockItem>", GTK_STOCK_CLOSE },
	{ "/File/Sep1", NULL, NULL, 0, "<Separator>", NULL },
	{ "/File/_Quit", NULL, OnExit, 1, "<StockItem>", GTK_STOCK_QUIT},
	{ "/_Edit", NULL,NULL, 0, "<Branch>",NULL},
	{ "/_?", NULL, NULL, 0, "<Branch>", NULL },
	{ "/?/_About...", "<CTRL>A", OnAbout, 1, "<StockItem>", GTK_STOCK_HELP}
};

/* Nombre d' éléments du menu */
static gint iNbMenuItem = sizeof(MenuItem) / sizeof(MenuItem[0]);

int main_gtk(int argc, char **argv)
{
	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pMenuBar;
	GtkItemFactory *pItemFactory;
	GtkAccelGroup *pAccel;

	gtk_init(&argc, &argv);

	/* Création de la fenêtre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "PicToText OCR");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 1550, 900);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Création de la table d'accélération */
	pAccel = gtk_accel_group_new();

	/* Création du menu */
	pItemFactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", pAccel);
	/* Récupération des éléments du menu */
	gtk_item_factory_create_items(pItemFactory, iNbMenuItem, MenuItem, (GtkWidget*)pWindow);
	/* Récupération du widget pour l'affichage du menu */
	pMenuBar = gtk_item_factory_get_widget(pItemFactory, "<main>");
	/* Ajout du menu en haut de la fenêtre */
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
	/* Association des raccourcis avec la fenêtre */
	gtk_window_add_accel_group(GTK_WINDOW(pWindow), pAccel);

	/* Création d un second menu de type GTK_TYPE_OPTION_MENU */
	pItemFactory = gtk_item_factory_new(GTK_TYPE_OPTION_MENU, "<main>", NULL);
	/* Récupération des éléments du menu */
	gtk_item_factory_create_items(pItemFactory, iNbMenuItem, MenuItem, (GtkWidget*)pWindow);
	/* Récupération du widget pour l'affichage du menu */
	pMenuBar = gtk_item_factory_get_widget(pItemFactory, "<main>");

	gtk_widget_show_all(pWindow);
	gtk_main();

	return EXIT_SUCCESS;
}
void create_file()
{
	GtkWidget *selection;

	selection = gtk_file_selection_new( g_locale_to_utf8( "Please, choose a path to load your image", -1, NULL, NULL, NULL) );
	gtk_widget_show(selection);

	//On interdit l'utilisation des autres fenêtres.
	gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(path), selection );

	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void path(GtkWidget *file_selection)
{
	const gchar* chemin;
	GtkWidget *dialog;
	chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );

	dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
					GTK_DIALOG_MODAL,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_OK,
					"You chose :\n%s", chemin);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	gtk_widget_destroy(file_selection);

	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pImage;
	GtkWidget *pQuitImage;
	GtkWidget *pQuitBtn;


	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
	gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Chargement d'une image a partir d'un fichier */
	pImage = gtk_image_new_from_file(chemin);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 5);

	pQuitBtn = gtk_button_new();
	gtk_box_pack_start(GTK_BOX(pVBox), pQuitBtn, TRUE, FALSE, 5);
	g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	/* Chargement d'une image a partir d'un GtkStockItem */
	pQuitImage = gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_LARGE_TOOLBAR);
	gtk_container_add(GTK_CONTAINER(pQuitBtn), pQuitImage);

	gtk_widget_show_all(pWindow);

}
void OnExit(gpointer data)
{
	GtkWidget *pQuestion;

	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
					GTK_DIALOG_MODAL,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Are you sure you want\n"
					"to exit PicToText?");

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

void OnOpen()
{
	create_file();
}

void OnAbout()
{
	GtkWidget *wind;
	wind = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(wind),320,200);
	gtk_window_set_title(GTK_WINDOW(wind), "Who are we?");

	GtkWidget *label = NULL;
	gchar* aboutUs;
	aboutUs = g_locale_to_utf8("The Running Coders vous presente son OCR\n"
			,-1, NULL, NULL, NULL);
	label = gtk_label_new(aboutUs);
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_container_add(GTK_CONTAINER(wind), label);
	gtk_widget_show_all(wind);
	g_signal_connect(G_OBJECT(wind),"destroy",
				G_CALLBACK(gtk_main_quit),NULL);
}
