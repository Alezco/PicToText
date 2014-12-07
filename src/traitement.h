#ifndef TRAIT_H
#define TRAIT_H

void convolution(SDL_Surface *surf, int size, float mat[][size]);
int IsValid(int x, int y, SDL_Surface *surface);
void grey(SDL_Surface *surface);
void binaire(SDL_Surface *surface);
int otsu(SDL_Surface *surface);

#endif
