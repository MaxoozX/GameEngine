/**
 * Header file for Sprite class.
 * @file Sprite.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Geometry.hpp"

#include "Sprite.hpp"

using namespace Geometry;

Sprite::Sprite(float x, float y, int width, int height, const char texturePath[], const char shapePath[], SDL_Renderer* renderer): m_x(x), m_y(y), m_width(width), m_height(height), m_renderer(renderer) {
      
      m_rect.x = x;
      m_rect.y = y;
      m_rect.w = width;
      m_rect.h = height;
      
      loadPolygons(shapePath);
      
    }

Sprite::Sprite(const Sprite &otherSprite): m_x(otherSprite.m_x), m_y(otherSprite.m_y), m_width(otherSprite.m_width), m_height(otherSprite.m_height) {
  
  m_rect.x = otherSprite.m_x;
  m_rect.y = otherSprite.m_y;
  m_rect.w = otherSprite.m_width;
  m_rect.h = otherSprite.m_height;
  
}

Sprite::~Sprite() = default;

void Sprite::loadPolygons(const char path[]) {
  
  shapePolygon = getPolygonFromPNG<float>(path);
  
  // Scale the polygon
  scaledPolygon = Polygon<float>(shapePolygon);
  
  double scaleFactorX = m_width / shapePolygon.m_w;
  double scaleFactorY = m_height / shapePolygon.m_h;
  
  for(auto &vertex : scaledPolygon.vertices) {
    vertex.x *= scaleFactorX;
    vertex.y *= scaleFactorY;
  }
  
  scaledPolygon.m_w = m_width;
  scaledPolygon.m_h = m_height;
  
  // Position the polygon
  displayPolygon = Polygon<float>(scaledPolygon);
  
  double deltaX = m_x - m_width / 2;
  double deltaY = m_y - m_height / 2;
  
  for(auto &vertex : scaledPolygon.vertices) {
    vertex.x += deltaX;
    vertex.y += deltaY;
  }
  
}

void Sprite::loadTexture(const char path[]) {
  m_texture = IMG_LoadTexture(m_renderer, path);
  if (m_texture == nullptr) {
    SDL_Log("Problem loading sprite texture : %s", IMG_GetError());
  }
}
