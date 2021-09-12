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
                polygon.vertices.push_back(Point<int>(column, row));
            }
        }
    }
    return polygon;
}

void drawPolygon(SDL_Renderer* renderer, Polygon<int>& poly, int offsetX = 0, int offsetY = 0, int coef = 0) {
    for(auto side: poly.sides) {
        SDL_RenderDrawLine(renderer, side.first.x, side.first.y, side.second.x, side.second.y);
    }

    for(auto diagonal: poly.diagonals) {
        SDL_RenderDrawLine(renderer, diagonal.first.x, diagonal.first.y, diagonal.second.x, diagonal.second.y);
    }
}

void displayVertex(Point<int> p) {
    SDL_Log("P(%d, %d)", p.x, p.y);
}

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Polygon collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 300, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    Polygon<int> polygon = getPolygonFromPNG("../assets/collision-points.png");
    Polygon<int> polygon2 = getPolygonFromPNG("../assets/collision-points2.png");

    int offsetX = 25;
    int offsetY = 17;
    int coef = 10;

    Polygon<int> polygonDisplay;
    Polygon<int> polygonDisplay2;

    for(const auto& vertex: polygon.vertices) {
        polygonDisplay.vertices.push_back(Point<int>(offsetX + vertex.x * coef, offsetY + vertex.y * coef));
    }

    for(const auto& vertex: polygon2.vertices) {
        polygonDisplay2.vertices.push_back(Point<int>(vertex.x * coef, vertex.y * coef));
    }

    SDL_Log("1");
    for(const auto& vertex: polygonDisplay.vertices) {
        displayVertex(vertex);
    }

    SDL_Log("2");
    for(const auto& vertex: polygonDisplay2.vertices) {
        displayVertex(vertex);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(polygonDisplay.checkValidity()) {
        polygonDisplay.computeMidPoint();
        polygonDisplay.computeSidesAndDiagonals();
        drawPolygon(renderer, polygonDisplay, offsetX, offsetY, coef);
    }

    if(polygonDisplay2.checkValidity()) {
        polygonDisplay2.computeMidPoint();
        polygonDisplay2.computeSidesAndDiagonals();
        drawPolygon(renderer, polygonDisplay2, 0, 0, coef);
    }

    std::pair<bool, Point<int>* > result = checkPolygonCollision(polygonDisplay, polygonDisplay2);

    if(result.first) {
        SDL_Log("Collision : %d, %d", result.second->x, result.second->y);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect;
        rect.x = result.second->x - 5;
        rect.y = result.second->y - 5;
        rect.w = 10;
        rect.h = 10;
        SDL_RenderDrawRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool quit = false;

    while(!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            SDL_Delay(10);
        }
    }

    SDL_Quit();

    return 0;
}