#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "detect.h"
#include <math.h>

#define Max(x, y) (((x) > (y)) ? (x) : (y))
#define Min(x, y) (((x) < (y)) ? (x) : (y))

void start()
{
		SDL_Surface *ecran = NULL, *image = NULL;
		SDL_Rect position;

		position.x = 0;
		position.y = 0;

		SDL_Init(SDL_INIT_VIDEO);
		image = IMG_Load("image/1.bmp");
		ecran = SDL_SetVideoMode(image->w, image->h, 32, SDL_HWSURFACE);
		SDL_WM_SetCaption("PicToText", NULL);

		//image = IMG_Load("src/image/1.bmp");

		processing(image,1,1,1);

		//SDL_BlitSurface(image, NULL, ecran, &position);

		SDL_Flip(ecran);
		//pause_p();

		SDL_FreeSurface(image);
		SDL_Quit();
}

void draw(SDL_Surface *surface, SDL_Rect rect, Uint32 color)
{
		for (int i = 0; i<rect.w; i++)
		{
				putpixel(surface,rect.x +  i,rect.y, color);
				putpixel(surface,rect.x +  i,rect.y + rect.h, color);
		}
		for (int j = 0; j<rect.h; j++)
		{
				putpixel(surface,rect.x,rect.y + j, color);
				putpixel(surface,rect.x +  rect.w,rect.y + j, color);
		}
}

void analysis_y(SDL_Surface *surface, int collumn[surface->h])
{
		Uint8 r, g, b;
		Uint32 pixel;
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		bool isempty;
		for (int j = 0; j < surface->h; j++)
		{
				isempty = true;
				for (int i = 0; i < surface->w; i++)
				{
						pixel = getpixel(surface,i,j);
						SDL_GetRGB(pixel,fmt,&r,&g,&b);
						if (r == 0 && g == 0 && b == 0)
						{
								isempty = false;
								break;
						}
				}
				if (isempty)
				{
						collumn[j] = 0;
				}
				else
				{
						collumn[j] = 1;
				}
		}
}

void analysis_x(SDL_Surface *surface, int row[surface->w])
{
		Uint8 r, g, b;
		Uint32 pixel;
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		bool isempty;
		for (int i = 0; i < surface->w; i++ )
		{
				isempty = true;
				for (int j = 0; j < surface->h; j++ )
				{
						pixel = getpixel(surface, i, j);
						SDL_GetRGB(pixel,fmt,&r,&g,&b);
						if (r == 0 && g == 0 && b == 0)
						{
								isempty = false;
								break;
						}
				}
				if (isempty)
				{
						row[i] = 0;
				}
				else
				{
						row[i] = 1;
				}
		}
}


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
		int bpp = surface->format->BytesPerPixel; 
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
						return 0;
		}
}


void analysis_x_2(SDL_Surface *surface, SDL_Rect rect, int tab[])
{
		Uint8 r, g, b;
		Uint32 pixel;
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		int x = rect.x;
		int y = rect.y;
		int w = rect.w;
		bool isempty;
		int h = rect.h;
		for (int i = 0; i < w ; i++)
		{
				isempty = true;
				for(int j = 0; j< h; j++)
				{
						pixel = getpixel(surface, i+x, j+y);
						SDL_GetRGB(pixel,fmt,&r,&g,&b);
						if (r == 0 && g == 0 && b == 0)
						{
								isempty = false;
								break;
						}
				}
				if (isempty)
				{
						tab[i] = 1;
				}
				else
				{
						tab[i] = 0;
				}
		}
}
void analysis_y_2(SDL_Surface *surface, SDL_Rect rect, int tab[])
{
		Uint8 r, g, b;
		Uint32 pixel;
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		int x = rect.x;
		int y = rect.y;
		int w = rect.w;
		bool isempty;
		int h = rect.h;
		for (int i = 0; i < h ; i++)
		{
				isempty = true;
				for(int j = 0; j< w; j++)
				{
						pixel = getpixel(surface, j+x, i+y);
						SDL_GetRGB(pixel,fmt,&r,&g,&b);
						if (r == 0 && g == 0 && b == 0)
						{
								isempty = false;
								break;
						}
				}
				if (isempty)
				{
						tab[i] = 1;
				}
				else
				{
						tab[i] = 0;
				}
		}
}
int detect_line(int g_tab_y[], SDL_Rect t_rect[], SDL_Rect rectangle_p)
{
		SDL_Rect rectangle;
		int count = 0;
		bool full_y = false;
		for (int i = 0; i<rectangle_p.h; i++)
		{
				if(g_tab_y[i] == 0 && !full_y)
				{
						full_y = true;
						rectangle.y = i+rectangle_p.y;
				}
				if (g_tab_y[i] == 1 && full_y) 
				{
						rectangle.h = i+rectangle_p.y - rectangle.y + 1;//
						rectangle.x = rectangle_p.x;
						rectangle.w = rectangle_p.w + 1;//
						t_rect[count] = rectangle;
						count++;
						full_y = false;
				}
		}
		return count;
}
int detect_char(int g_tab_x[], SDL_Rect t_rect[], SDL_Rect rectangle_p)
{
		SDL_Rect rectangle;
		int count = 0;
		bool full_x = false;
		for (int i = 0; i<rectangle_p.w; i++)
		{
				if(g_tab_x[i] == 0 && !full_x)
				{
						full_x = true;
						rectangle.x = i+rectangle_p.x;
				}
				if (g_tab_x[i] == 1 && full_x) 
				{
						rectangle.w = i+rectangle_p.x - rectangle.x;
						rectangle.y = rectangle_p.y;
						rectangle.h = rectangle_p.h;
						t_rect[count] = rectangle;
						count++;
						full_x = false;
				}
		}
		return count;
}


int detect_block(SDL_Surface *surface,int tab_x[],SDL_Rect t_rect[surface->w])
{
		bool start = false;
		int count = 0;
		SDL_Rect rectangle;
		for (int i = 0; i < surface->w; i++)
		{
				if (tab_x[i] == 1 && !start)
				{
						start = true;
						rectangle.x = i;
				}
				if (tab_x[i] == 0 && start)
				{
						start = false;
						rectangle.h = surface->h;
						rectangle.y = 0;
						rectangle.w = i - rectangle.x;
						t_rect[count] = rectangle;
						count++;

				}
		}
		return count;
}

int getspace(SDL_Rect rect[], int size, SDL_Rect t_rect[])
{
		int space = 0;
		int sum = 0;
		int rect_c = 0;
		for (int i = 0; i < size-1; i++)
		{
				space = (rect[i+1].x - (rect[i].x+rect[i].w)) + space;
				sum++;
		}
		int ref = space / sum;
		for (int i = 0; i < size-1; i++)
		{
				SDL_Rect nr;
				if (rect[i+1].x - (rect[i].x+rect[i].w) > ref)
				{
						nr.x = rect[i].x + rect[i].w;
						nr.h = rect[i].h;
						nr.y = rect[i].y;
						nr.w = rect[i+1].x - (rect[i].x+rect[i].w);
						//printf("%d %d %d %d \n",nr.x,nr.y,nr.w,nr.h );
						t_rect[rect_c] = nr;
						rect_c++;
				}
		}
		return rect_c;
}

void processing(SDL_Surface *surface, int lvl1, int lvl2, int lvl3)
{
	  int bin[surface->w*surface->h];
		int test = 0;
		int plop[1000];
		int resized[1000];
		SDL_PixelFormat *fmt;
		Uint32 pixel_red, pixel_green, pixel_blue, pixel_yellow;
		fmt = surface->format;
		pixel_red = SDL_MapRGB(fmt, 255, 0, 0);
		pixel_green = SDL_MapRGB(fmt, 0, 255, 0);
		pixel_blue = SDL_MapRGB(fmt, 0, 0, 255);
		pixel_yellow = SDL_MapRGB(fmt, 255, 255, 0);

		int x[surface->w];
		analysis_x(surface, x);
		int y[surface->h];
		analysis_y(surface, y);

		SDL_Rect rect_b[(surface->w*surface->h)/4];
		int rect_size_t_b = 0;
		rect_size_t_b = detect_block(surface,x, rect_b);

		for (int i = 0; i<rect_size_t_b; i++)
		{
				int y2[surface->h];
				analysis_y_2(surface, rect_b[i], y2);
				SDL_Rect rect[(rect_b[i].h*rect_b[i].w)/5];
				int rect_size_t;
				rect_size_t = detect_line(y2,rect,rect_b[i]);

				for (int j = 0; j < rect_size_t; j++)
				{
						SDL_Rect rect_c[(rect[j].w*rect[j].h)/5];
						int tab[rect[j].w];
						analysis_x_2(surface, rect[j], tab);

						int rect2_size_t = detect_char(tab, rect_c, rect[j]);
						//
						SDL_Rect rect_espace[(rect[j].w*rect[j].h)/5];
						int data = getspace(rect_c,rect2_size_t,rect_espace);

						//
						for (int z = 0; z < rect2_size_t; z++)
						{
								int y2_2[rect_c[z].h];
								analysis_y_2(surface, rect_c[z], y2_2);
								SDL_Rect rect_r[(rect_c[z].h*rect_c[z].w)/5];
								int rect_size_r;
								rect_size_r = detect_line(y2_2,rect_r,rect_c[z]);
								for (int k = 0; k < data; k++)
								{
										if (lvl1 == 1)
										{
												//draw(surface, rect_r[k], pixel_green);
												draw(surface, rect_espace[k],pixel_yellow);

												//ligne code hadrien
												if (test < 26)
												{
													squareBorder(surface ,bin, plop, rect_r[k], calcul_m(rect_r[k].h,rect_r[k].w));
													 print_matrix(plop, calcul_m(rect_r[k].h,rect_r[k].w),calcul_m(rect_r[k].h,rect_r[k].w));
													 printf("\n\n");
													 resizePixels(plop,calcul_m(rect_r[k].h,rect_r[k].w),calcul_m(rect_r[k].h,rect_r[k].w), 32, 32, resized);
															 print_matrix(resized, 32,32);
																									 			 test++;}
										}
								}
						}
						if (lvl2 == 1) 
						{
								draw(surface, rect[j], pixel_red);
						}
				}
				if (lvl3 == 1)
				{
						draw(surface, rect_b[i], pixel_blue);
				}
		}
		SDL_SaveBMP(surface, "sortie");
}

void pause_p()
{
		int ok = 1;
		SDL_Event event;

		while (ok)
		{
				SDL_WaitEvent(&event);
				switch(event.type)
				{
						case SDL_QUIT:
								ok = 0;
				}
		}
}

void resizePixels(int pixels[],int w1,int h1,int w2,int h2, int tmp[w2*h2])
{
		double x_ratio = w1/(double)w2 ;
		double y_ratio = h1/(double)h2 ;
		double px, py ; 
		for (int i=0;i<h2;i++)
		{
				for (int j=0;j<w2;j++)
				{
						px = floor(j*x_ratio) ;
						py = floor(i*y_ratio) ;
						tmp[(i*w2)+j] = pixels[(int)((py*w1)+px)] ;
				}
		}
}

void print_matrix(int matrix[], int h, int w)
{
		int c = 0;
		for (int i = 0; i < w; i++)
		{
				printf("\n");
				for (int j = 0; j < h; j++)
				{
						if (matrix[c] == 1)
						{
								printf("%d ", matrix[c]);
						}
						else
								printf(" ");
						c++;
				}
		}
}
int calcul_m(int x, int y)
{
		if (x >= y)
		{
				return x;
		}
		else
		{
				return y;
		}
}
void squareBorder(SDL_Surface *surface, int Tab[], 
				int cTab[], SDL_Rect rect, int m)
{
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		int w = surface->w;

		if(m == rect.h)
		{
				int nbWhCol = (m - rect.w) /2;

				for(int x = 0; x < m; x++)
				{
						for(int y = 0; y < m; y++)
						{
								if(x < nbWhCol || x > (nbWhCol + rect.w))
								{
										cTab[(y*m)+x] = 0;
								}
								else
								{
										cTab[(y*m)+x] = Tab[((y+rect.y)*w)+(x+rect.x-nbWhCol)];
								}
						}
				}
		}
		else
		{
				int nbWhRow = (m - rect.h) /2;

				for(int y = 0; y < m; y++)
				{
						for(int x = 0; x < m; x++)
						{
								if(y < nbWhRow || y > (nbWhRow + rect.h))
								{
										cTab[(y*m)+x] = 0;
								}
								else
								{
										cTab[(y*m)+x] = Tab[((y+rect.y)*w)+(x+rect.x*nbWhRow)];
								}
						}
				}
		}
		return;
}

void toBinary(SDL_Surface *surface, int data[surface->w*surface->h])
{
		int c = 0;
		Uint8 r, g, b;
		Uint32 pixel;
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		int w = surface->w;
		for (int i = 0; i < surface->w; i++)
		{
				for (int j = 0; j < surface->h; j++)
				{
						pixel = getpixel(surface,i,j);
						SDL_GetRGB(pixel,fmt,&r,&g,&b);
						if (r == 0 && g == 0 && b == 0)
						{
								data[j*w + i] = 1;
								c++;
						}
						else
						{
								data[j*w + i] = 0;
								c++;
						}
				}
		}
}
