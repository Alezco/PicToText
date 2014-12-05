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
	{
		start(argv[1],'b');
	}
	else
	{
		start("image/arial.jpg", 'b');
	}*/

	/*SDL_Surface *ecran = NULL, *image = NULL;
		SDL_Rect position;

		position.x = 0;
		position.y = 0;

		SDL_Init(SDL_INIT_VIDEO);*/

	//main_gtk(argc, argv);

	/*ecran = SDL_SetVideoMode(image->w, image->h, 32, SDL_HWSURFACE);
		SDL_WM_SetCaption("PicToText", NULL);*/

	//processing(image, lvl1, lvl2, lvl3);

	/*SDL_BlitSurface(image, NULL, ecran, &position);

		SDL_Flip(ecran);
		pause();

		SDL_FreeSurface(image);
		SDL_Quit();
		printf("EXIT WITH SUCESS !\n");*/

	return EXIT_SUCCESS;
}
