#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "detect.h"

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



void processing(SDL_Surface *surface, int lvl1, int lvl2, int lvl3)
{
    SDL_PixelFormat *fmt;
    Uint32 pixel_red, pixel_green, pixel_blue;
    fmt = surface->format;
    pixel_red = SDL_MapRGB(fmt, 255, 0, 0);
    pixel_green = SDL_MapRGB(fmt, 0, 255, 0);
    pixel_blue = SDL_MapRGB(fmt, 0, 0, 255);
    
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
	   for (int z = 0; z < rect2_size_t; z++)
	   {
	     int y2_2[rect_c[z].h];
	     analysis_y_2(surface, rect_c[z], y2_2);
	     SDL_Rect rect_r[(rect_c[z].h*rect_c[z].w)/5];
	     int rect_size_r;
	     rect_size_r = detect_line(y2_2,rect_r,rect_c[z]);
	     for (int k = 0; k < rect_size_r; k++)
	       {
		 if (lvl1 == 1)
		   {
		     draw(surface, rect_r[k], pixel_green);
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

