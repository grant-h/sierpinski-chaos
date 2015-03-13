#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>

#define WIDTH 1000
#define HEIGHT 640

using namespace std;

struct rgb_t
{
  uint8_t r,g,b,a;
};

void setPoint(SDL_Renderer * sRender, int x, int y, rgb_t color);
void setPoint(SDL_Renderer * sRender, SDL_Point * pt, rgb_t color);
rgb_t color(int r, int g, int b);
void die(const char * msg);
void setSeed(int seed);

#define ITER 100000

int main(int argc, char * argv[])
{
  SDL_Renderer * sRender;
  SDL_Window * sWin;

  //setup the window and renderer: TODO make this in to individual calls
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &sWin, &sRender);

  if(!sRender || !sWin)
    die("Could not create a window or renderer!\n");
  
  //clear the screen
  SDL_SetRenderDrawColor(sRender, 0, 0, 0, 255);
  SDL_RenderClear(sRender);

  SDL_Point last = {WIDTH, HEIGHT};
  SDL_Point * points = new SDL_Point[ITER];
  int * colors = new int[ITER];
  SDL_Point tri[3];

  int curIter = 0;

  tri[0].x = WIDTH/2;
  tri[0].y = 0;
  tri[1].x = 0;
  tri[1].y = HEIGHT;
  tri[2].x = WIDTH;
  tri[2].y = HEIGHT;
  /*tri[3].x = tri[0].x + (tri[1].x-tri[0].x)/2;
  tri[3].y = HEIGHT/2;*/

  //main loop
  while(1)
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
      case SDL_KEYDOWN:
      {
        if(event.key.keysym.sym == SDLK_r)
        {
        }
        else
        {
          return 0;
        }
      }
      case SDL_MOUSEMOTION:
        /*if(selected)
        {
          viewport.x -= event.motion.xrel;
          viewport.y -= event.motion.yrel;
        }*/
        break;
      case SDL_MOUSEBUTTONDOWN:
        //selected = true;
        break;
      case SDL_MOUSEBUTTONUP:
        //selected = false;
        break;
      }
    }


    SDL_SetRenderDrawColor(sRender, 0, 0, 0, 255);
    SDL_RenderClear(sRender);

    setPoint(sRender, &tri[0], color(255, 0, 0));
    setPoint(sRender, &tri[1], color(0, 255, 0));
    setPoint(sRender, &tri[2], color(0, 0, 255));

    for(int i = 0; i < curIter; i++)
    {
      if(colors[i] == 0)
        setPoint(sRender, &points[i], color(255, 0, 0));
      else if(colors[i] == 1)
        setPoint(sRender, &points[i], color(0, 255, 0));
      else if(colors[i] == 2)
        setPoint(sRender, &points[i], color(0, 0, 255));
      else if(colors[i] == 3)
        setPoint(sRender, &points[i], color(0, 128, 128));
      else if(colors[i] == 4)
        setPoint(sRender, &points[i], color(0, 128, 128));
    }

    if(curIter < ITER)
    {
      int choice = rand() % (sizeof(tri)/sizeof(*tri));
      int dx = (tri[choice].x -last.x)/2;
      int dy = (tri[choice].y -last.y)/2;

      points[curIter].x = last.x + dx;
      points[curIter].y = last.y + dy;
      colors[curIter] = choice;

      last = points[curIter];
      curIter++;
    }

    SDL_RenderPresent(sRender);

    //SDL_Delay(10);
  }

  SDL_Quit();

  return 0;
}

void setPoint(SDL_Renderer * sRender, int x, int y, rgb_t color)
{
  SDL_SetRenderDrawColor(sRender, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(sRender, x, y);
  /*SDL_RenderDrawPoint(sRender, x+1, y);
  SDL_RenderDrawPoint(sRender, x, y+1);
  SDL_RenderDrawPoint(sRender, x+1, y+1);*/
}

void setPoint(SDL_Renderer * sRender, SDL_Point * pt, rgb_t color)
{
  setPoint(sRender, pt->x, pt->y, color);
}

rgb_t color(int r, int g, int b)
{
  rgb_t color = {r, g, b, 0};

  return color;
}

void die(const char * msg)
{
  cout << msg << std::endl;
  exit(1);
}
