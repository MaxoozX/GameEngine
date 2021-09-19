/**
 * Implementation file for Missile class.
 * @file Missile.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>

#include "Missile.hpp"
#include "Sprite.hpp"

Missile::Missile(SDL_Renderer* renderer,int windowWidth, int windowHeight, int x, int y, float velocityX, float velocityY, bool _isFromPlayer): Sprite::Sprite(x, y, 10, 20, renderer, 10), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_velocity(velocityX, velocityY), fromPlayer(_isFromPlayer) {
    minPosX = - m_width / 2;
    maxPosX = m_windowWidth + m_width / 2;
    minPosY = - m_height / 2;
    maxPosY = m_windowHeight + m_height / 2;
}

void Missile::load() {
    loadTexture("assets/missile-texture.png");
}

void Missile::updateRectAndPolygon() {
    double deltaX = center.x - m_width / 2;
    double deltaY = center.y - m_height / 2;
    int pixelDelta = m_pixelSize / 2;

    m_rect.x = deltaX;
    m_rect.y = deltaY;
    // positionDisplayPolygon(deltaX + pixelDelta, deltaY + pixelDelta);
    positionDisplayPolygon(deltaX, deltaY);
}

bool Missile::isVisible() {
    return (center.x > minPosX && center.x < maxPosX && center.y > minPosY && center.y < maxPosY);
}

bool Missile::isFromPlayer() {
    return fromPlayer;
}

void Missile::applyVelocity() {
    center += m_velocity;
}
