#ifndef DETECT_H
#define DETECT_H

void pause();
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void draw(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void analyse_y(SDL_Surface *surface, int collumn[surface->h]);
void analyse_x(SDL_Surface *surface, int row[surface->w]);
void analyse_x_2(SDL_Surface *surface, SDL_Rect rect, int tab[]);
void analyse_y_2(SDL_Surface *surface, SDL_Rect rect, int tab[]);
int fonction_char(int g_tab_x[], SDL_Rect t_rect[], SDL_Rect rectangle_p);
int fonction_line(int g_tab_y[], SDL_Rect t_rect[], SDL_Rect rectangle_p);
int fonction_bloc(SDL_Surface *surface, int tab_x[], SDL_Rect t_rect[surface->w]);
void traitement(SDL_Surface *surface, int lvl1, int lvl2, int lvl3);

#endif
