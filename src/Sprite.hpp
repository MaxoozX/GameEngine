/**
 * Implementation file for Sprite class.
 * @file Sprite.cpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Geometry.hpp"

/**
 * The Sprite class
*/
class Sprite {
  /*
  The class needs to have a corresponding rectangle, polygon, and texture, with some internal state.
  */
  
  public:
    float m_x;
    float m_y;
    int m_width;
    int m_height;
    SDL_Rect m_rect;
    Geometry::Polygon<float> shapePolygon, scaledPolygon, displayPolygon;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;
    
    // Methods
    Sprite(float = 0, float = 0, int = 0, int = 0, const char[] = nullptr, const char[] = nullptr, SDL_Renderer* = nullptr);
    Sprite(const Sprite &);
    ~Sprite();
    
    void loadPolygons(const char[]);
    
    void loadTexture(const char[]);
    
};

#endif // SPRITE_H