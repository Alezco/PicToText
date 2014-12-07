#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "detect.h"
#include "neuralnetwork.h"
#include "gtk.h"

int main(int argc, char *argv[])
{
	printf("STARTING ...\n");

	main_gtk(argc,argv);
	/*if(argc > 2)
	{
		char a = *argv[1];
		start(argv[2], a);
	}
	else if (argc > 1)
		start(argv[1],'b');
	else
	start("image/arial.jpg", 'b');*/

	return EXIT_SUCCESS;
}
