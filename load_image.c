#include <stdio.h>
#include <stdlib.h>
#include "load_image.h"

void Printlol()
{
	image = gtk_image_new_from_file("guillaume.png");
	gtk_container_add(GTK_CONTAINER (window), image);
	gtk_widget_show(image);
	gtk_widget_show(window);
}
