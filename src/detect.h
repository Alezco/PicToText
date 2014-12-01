#ifndef DETECT_H
#define DETECT_H

void start();
void pause_p();
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void draw(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void analysis_y(SDL_Surface *surface, int collumn[surface->h]);
void analysis_x(SDL_Surface *surface, int row[surface->w]);
void analysis_x_2(SDL_Surface *surface, SDL_Rect rect, int tab[]);
void analysis_y_2(SDL_Surface *surface, SDL_Rect rect, int tab[]);
int detect_char(int g_tab_x[], SDL_Rect t_rect[], SDL_Rect rectangle_p);
int detect_line(int g_tab_y[], SDL_Rect t_rect[], SDL_Rect rectangle_p);
int detect_block(SDL_Surface *surface,int tab_x[],SDL_Rect t_rect[surface->w]);
void processing(SDL_Surface *surface, int lvl1, int lvl2, int lvl3);

#endif
