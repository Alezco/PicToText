#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
 
void pause();
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);

void remplir_x(SDL_Surface *surface, int x, Uint32 pixel)
{
  for (int i = 0; i<surface->h - 1; i++)
    {
      putpixel(surface, x, i, pixel); 
    }
}
void remplir_y(SDL_Surface *surface, int y, Uint32 pixel)
{
  for (int j = 0; j<surface->w - 1; j++)
    {
      putpixel(surface, j, y, pixel); 
    }
}

int * x_sequence(SDL_Surface *surface, int x)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  SDL_PixelFormat *fmt;
  static int line[3000];
  fmt = surface->format;
    for (int i = 0; i < surface->h; i++ )
    {
      pixel = getpixel(surface,x,i);
      SDL_GetRGB(pixel,fmt,&r,&g,&b);
      if (r == 0 && g == 0 && b == 0)
	{
	  line[i] = 1;
	}
      else
	{
	  line[i] = 0;
	}
    }
  return line;
}

/*void post_traitement(SDL_Surface *surface)
{
  
}*/
void traitement(SDL_Surface *surface, int* tab, char info)
{
  Uint32 pixel_rouge;
  SDL_PixelFormat *fmt;
  fmt = surface->format;
  pixel_rouge  = SDL_MapRGB(fmt, 255, 0, 0);
  if (info == 'x')
    {
      for (int x = 1; x < (surface->w) - 1; x++ )
	{
	  if (tab[x] != tab[x+1])
	  {
	    // if (x > (surface->w)/2)
	    //	{
	    //	  remplir_x(surface, x+1, pixel_rouge);
	    //	}
	    //else
	    //	{
		  remplir_x(surface, x, pixel_rouge);
		  //	}
	    }
	}
    }
  if (info == 'y')
    {
     for (int y = 1; y < (surface->h) - 1; y++ )
	{
	  if (tab[y] != tab[y+1])
	    {
	      //if (y > (surface->h)/2)
	      //{
	      //remplir_y(surface, y+1, pixel_rouge);
		  //	}
		  // else
		  //{
		    remplir_y(surface, y, pixel_rouge);
		  //}
	    }
	}
    }
}
int* analyse_y(SDL_Surface *surface)
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint32 pixel;
  SDL_PixelFormat *fmt;
  fmt = surface->format;
  static int collumn[3000];
  bool estvide;
  for (int j = 0; j < surface->h; j++ )
  {
    estvide = true;
    for (int i = 0; i < surface->w; i++ )
    {
      pixel = getpixel(surface,i,j);
      SDL_GetRGB(pixel,fmt,&r,&g,&b);
      if (r == 0 && g == 0 && b == 0)
	{
	  estvide=false;
	  break;
	}
    }
    if (estvide)
      {
	collumn[j] = 0;
      }
    else
      {
	collumn[j] = 1;
      }
  }
  return collumn;
}
int* analyse_x(SDL_Surface *surface)
{
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint32 pixel;
  SDL_PixelFormat *fmt;
  fmt = surface->format;
  static int collumn[3000];
  bool estvide;
  for (int i = 0; i < surface->w; i++ )
  {
    estvide = true;
    for (int j = 0; j < surface->h; j++ )
    {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel,fmt,&r,&g,&b);
      if (r == 0 && g == 0 && b == 0)
	{
	  estvide=false;
	  break;
	}
    }
    if (estvide)
      {
	collumn[i] = 0;
      }
    else
      {
	collumn[i] = 1;
      }
  }
  return collumn;
}

void action(SDL_Surface *surface)
{
  Uint32 pixel_rouge;
  
  int x = 0;
  int y = 0;
 
  /*bool estvide_droite;
  bool estvide_gauche;
  bool estvide_haut;
  bool estvide_bas;*/
  bool estvide;
  
  
  SDL_PixelFormat *fmt;
  fmt = surface->format;
  pixel_rouge  = SDL_MapRGB(fmt, 255, 0, 0);
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;

  for (x = 0; x < surface->w; x++ )
  {
    estvide = true;
    for (y = 0; y < surface->h; y++ )
    {
      pixel = getpixel(surface,x,y);
      SDL_GetRGB(pixel,fmt,&r,&g,&b);
      if (r == 0 && g == 0 && b == 0)
	{
	  estvide = false;
	  printf("Ligne occupé ");
	  break;
	}
    }
    if (estvide)
      {
	remplir_x(surface, x, pixel_rouge);
      }
  }

  for (y = 0; y < surface->h; y++ )
  {
    estvide = true;
    for (x = 0; x < surface->w; x++ )
    {
      pixel = getpixel(surface,x,y);
      SDL_GetRGB(pixel,fmt,&r,&g,&b);
      if (r == 0 && g == 0 && b == 0)
	{
	  estvide = false;
	  printf("Ligne occupé ");
	  break;
	}
    }
    if (estvide)
      {
	//remplir_y(surface, y, pixel_rouge);
      }
  }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

int main()
{
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *sapin = NULL;
    SDL_Rect positionFond, positionSapin;
     SDL_PixelFormat *fmt;

    positionFond.x = 0;
    positionFond.y = 0;
    positionSapin.x = 500;
    positionSapin.y = 260;
 
    SDL_Init(SDL_INIT_VIDEO);

 
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
 
    imageDeFond = IMG_Load("src/perfect_image.jpg");
    
    Uint32 pixel;
    fmt = imageDeFond->format;
    pixel = SDL_MapRGB(fmt, 255, 0, 0);
    /*putpixel(imageDeFond, 0, 0, pixel);
    remplir_x(imageDeFond, 10, pixel);
    remplir_y(imageDeFond, 10, pixel);*/

    //action(imageDeFond);
    int *x;
    x = analyse_x(imageDeFond);
    int *y;
    y = analyse_y(imageDeFond);
    for(int i=0; i<imageDeFond->w; i++)
      {
	printf("%d", x[i]);
      }
    for(int i=0; i<imageDeFond->h; i++)
      {
	printf("%d", y[i]);
      }
    traitement(imageDeFond, x, 'x');
    traitement(imageDeFond, y, 'y');
    //action(imageDeFond);
    
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
 
    /* Chargement d'un PNG avec IMG_Load
    Celui-ci est automatiquement rendu transparent car les informations de
    transparence sont codées à l'intérieur du fichier PNG */
 
    SDL_Flip(ecran);
    pause();
 
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(sapin);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}
 
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
