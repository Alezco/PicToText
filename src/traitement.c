#include "traitement.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "detect.h"

void grey(SDL_Surface *surface)
{
  Uint32 pixel, new_pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 grey;
  for (int i = 0; i<surface->w; i++)
    {
      for (int j = 0; j<surface->h; j++)
	{
	  pixel = getpixel(surface, i, j);
	  SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	  grey = ( r * 0.3 + g * 0.59 + b * 0.11)/3;
	  new_pixel = SDL_MapRGB(surface->format,grey,grey,grey);
	  putpixel(surface, i, j, new_pixel);
	}
    }
}

int greyref(SDL_Surface *surface, int x, int y)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 grey;

 pixel = getpixel(surface, x, y);
 SDL_GetRGB(pixel, surface->format, &r, &g, &b);
 grey = ( r * 0.3 + g * 0.59 + b * 0.11)/3;
 return b;
}

void binaire(SDL_Surface *surface)
{
  int seuil = otsu(surface);
  if (seuil == 0)
    {
      return;
    }
  Uint32 pixel, pixel_n, pixel_b;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  pixel_n = SDL_MapRGB(surface->format, 0, 0, 0);
  pixel_b = SDL_MapRGB(surface->format, 255, 255, 255);
  for (int i = 0; i<surface->w; i++)
    {
      for (int j = 0; j<surface->h; j++)
	{
	  pixel = getpixel(surface, i, j);
	  SDL_GetRGB(pixel, surface->format, &r, &g, &b);
	  if (r < seuil)
	    {
	      putpixel(surface, i, j, pixel_n);
	    }
	  else
	    {
	      putpixel(surface, i, j, pixel_b);
	    }
	}
    }
}

/*Otsu : defini la sensibilite appropriee*/
int otsu(SDL_Surface *surface)
 
{
  int gray_levels = 256;
  int y_size1 = surface->h, x_size1 = surface->w, size = y_size1 * x_size1;
  int hist[gray_levels];//nombre de gris
  double prob[gray_levels], omega[gray_levels]; //probabilite de gris
  double myu[gray_levels];   /*somme de chaque proba * niveau
                               de gris pour calculer l'eperance*/
  double max_sigma, sigma[gray_levels]; //variance
  int i, x, y;
  int threshold; //seuil
 
  /*creation de l'histogramme*/
  for (i = 0; i < gray_levels; i++) hist[i] = 0;
  for (y = 0; y < y_size1; y++)
    for (x = 0; x < x_size1; x++) {
      hist[greyref(surface,x,y)]++;
    }
  /*creation des probabilite pour chaque gris*/
  for ( i = 0; i < gray_levels; i ++ ) {
    prob[i] = (double)hist[i] / size;
  }
 
  /*creation de la moyenne et de l'esperance*/
  omega[0] = prob[0];
  myu[0] = 0.0; //jamais de noir pour faciliter les calculs
  for (i = 1; i < gray_levels; i++) {
    omega[i] = omega[i-1] + prob[i];
    myu[i] = myu[i-1] + i*prob[i];
  }
 
  //sigma calcul la variance inter class
 
  threshold = 0;
  max_sigma = 0.0;
  for (i = 0; i < gray_levels-1; i++) {
    if (omega[i] != 0.0 && omega[i] != 1.0)
      sigma[i] = (myu[gray_levels-1]*omega[i] - myu[i])*
        (myu[gray_levels-1]*omega[i] - myu[i]) /
        (omega[i]*(1.0 - omega[i]));//Formule d'Otsu
    else
      sigma[i] = 0.0;
    if (sigma[i] > max_sigma) {
      max_sigma = sigma[i];
      threshold = i;
    }
  }
  printf("treshold = %d", threshold);
  return threshold;
}
