#include <cstdlib>
#include <cmath> // Need to compile with -lm
#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // To load the texture (IMG_...)

#include "Geometry.hpp"

using namespace std;
using namespace Geometry;

Polygon<int> getPolygonFromPNG(const char path[]) {
    SDL_Surface *surface = IMG_Load(path);
    int *pixels = (int*)surface->pixels;
    Polygon<int> polygon;
    for(int row = 0; row < surface->h; row++) {
        for(int column = 0; column < surface->w; column++) {
            int pixel = pixels[row*surface->w+column];
            int alpha = (pixel >> 24) & 0xFF;
            int red = (pixel >> 16) & 0xFF;
            int green = (pixel >> 8) & 0xFF;
            int blue = pixel & 0xFF;
            if(alpha > 0) {
                polygon.vertices.push_back(Point2d<int>(column, row));
            }
        }
    }
    return polygon;
}

void drawPolygon(SDL_Renderer* renderer, Polygon<int>& poly) {
    for(auto side: poly.sides) {
        SDL_RenderDrawLine(renderer, side.first.x, side.first.y, side.second.x, side.second.y);
    }

    for(auto diagonal: poly.diagonals) {
        SDL_RenderDrawLine(renderer, diagonal.first.x, diagonal.first.y, diagonal.second.x, diagonal.second.y);
    }
}

void displayVertex(Point2d<int> p) {
    SDL_Log("P(%d, %d)", p.x, p.y);
}

void computePosAndCollision(SDL_Renderer* renderer, Polygon<int> &poly1, Polygon<int> &poly2) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  poly1.computeMidPoint();
  poly1.computeSidesAndDiagonals();
  drawPolygon(renderer, poly1);
  
  drawPolygon(renderer, poly2);

  std::pair<bool, Point2d<int>* > result = checkPolygonCollision(poly1, poly2);

  if(result.first) {
      // SDL_Log("Collision : %d, %d", result.second->x, result.second->y);
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_Rect rect;
      rect.x = result.second->x - 5;
      rect.y = result.second->y - 5;
      rect.w = 10;
      rect.h = 10;
      SDL_RenderDrawRect(renderer, &rect);
  }
  
  SDL_RenderPresent(renderer);
}

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Polygon collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 300, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    Polygon<int> polygon = getPolygonFromPNG("../assets/collision-points.png");
    Polygon<int> polygon2 = getPolygonFromPNG("../assets/collision-points2.png");

    int curPosX = 20;
    int curPosY = 15;
    int coef = 10;

    // Creating the actual polygons that'll be used
    /*--------------*/
    Polygon<int> polygonResized(polygon);
    Polygon<int> polygonResized2(polygon2);

    for(auto& vertex: polygonResized.vertices) {
        vertex.x *= coef;
        vertex.y *= coef;
    }

    for(auto& vertex: polygonResized2.vertices) {
        vertex.x *= coef;
        vertex.y *= coef;
    }
    
    Polygon<int> polygonDisplay(polygonResized);
    Polygon<int> polygonDisplay2(polygonResized2);
    
    for(auto& vertex: polygonDisplay.vertices) {
        vertex.x += curPosX;
        vertex.y += curPosY;
    }
    
    if(polygonDisplay2.checkValidity()) {
      polygonDisplay2.computeMidPoint();
      polygonDisplay2.computeSidesAndDiagonals();
      drawPolygon(renderer, polygonDisplay2);
    }
    /*--------------*/

    // Computing the values and checking for collision
    /*--------------*/
    computePosAndCollision(renderer, polygonDisplay, polygonDisplay2);
    /*--------------*/
    
    SDL_Event event;
    bool quit = false;
    int waitTime = 1000 / 60;
    int lastTime;
    int timeElapsed;
    int timeToWait;
    bool leftPressed = false, rightPressed = false, upPressed = false, downPressed = false;

    while(!quit) {
        
      lastTime = SDL_GetTicks();
    
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        
        switch (event.type) {

          case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
              switch (event.key.keysym.sym) {
                
                case SDLK_DOWN:
                  downPressed = true;
                  break;
                  
                case SDLK_UP:
                  upPressed = true;
                  break;
                  
                case SDLK_LEFT:
                  leftPressed = true;
                  break;
                  
                case SDLK_RIGHT:
                  rightPressed = true;
                  break;
      
                default:
                  break;
              }
            }
            break;
    
          case SDL_KEYUP:
            if (event.key.repeat == 0) {
              switch (event.key.keysym.sym) {
    
                case SDLK_DOWN:
                  downPressed = false;
                  break;
                  
                case SDLK_UP:
                  upPressed = false;
                  break;
                  
                case SDLK_LEFT:
                  leftPressed = false;
                  break;
                  
                case SDLK_RIGHT:
                  rightPressed = false;
                  break;
      
                default:
                  break;
              }
            }
            break;
    
          default:
            break;
        }
      }
      
      if(leftPressed) {
        curPosX -= 5;
      }
      if(rightPressed) {
        curPosX += 5;
      }
      if(upPressed) {
        curPosY -= 5;
      }
      if(downPressed) {
        curPosY += 5;
      }
      
      // I can either generate a new polygon, or use the already existant one
      polygonDisplay = Polygon<int>(polygonResized);
      
      for(auto& vertex: polygonDisplay.vertices) {
          vertex.x += curPosX;
          vertex.y += curPosY;
      }
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      
      computePosAndCollision(renderer, polygonDisplay, polygonDisplay2);
      
      
      timeElapsed = SDL_GetTicks() - lastTime; // In ms
      timeToWait = waitTime - timeElapsed;
      
      if (timeToWait > 0) {
        SDL_Delay(timeToWait);
      }
    }

    SDL_Quit();

    return 0;
}