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
  //main_gtk(argc, argv);
    printf("STARTING ...\n");
    //main_neural();
    /*SDL_Surface *ecran = NULL, *image = NULL;
    SDL_Rect position;

    position.x = 0;
    position.y = 0;
 
    SDL_Init(SDL_INIT_VIDEO);*/
    
    int lvl1, lvl2, lvl3;
    lvl1 = 1;
    lvl2 = 1;
    lvl3 = 1;
    if (argc < 2)
     {
       //image = IMG_Load("src/image/1.bmp");
     }
     else
     {
       // image = IMG_Load(argv[1]);
	if (argc == 3)
	  {
	    lvl1 = atoi(argv[2]);
	  }
	if (argc == 4)
	  {
	    lvl1 = atoi(argv[2]);
	    lvl2 = atoi(argv[3]);
	  }
	if (argc == 5)
	  {
	    lvl1 = atoi(argv[2]);
	    lvl2 = atoi(argv[3]);
	    lvl3 = atoi(argv[4]);
	  }
	
	
     }
 
    main_gtk(argc, argv);

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
