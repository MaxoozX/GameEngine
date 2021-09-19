/**
 * Implementation file for Enemy class.
 * @file Enemy.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>

#include "Enemy.hpp"
#include "Sprite.hpp"

Enemy::Enemy(SDL_Renderer* renderer,int windowWidth, int windowHeight, int x, int y, float velocityX, float velocityY, bool doesShoot): Sprite::Sprite(x, y, 80, 80, renderer, 10), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_velocity(velocityX, velocityY), shooter(doesShoot) {
    minPosX = - m_width / 2;
    maxPosX = m_windowWidth + m_width / 2;
    minPosY = - m_height / 2;
    maxPosY = m_windowHeight + m_height / 2;
}

void Enemy::load() {
    loadTexture("assets/enemy-texture.png");
}

void Enemy::updateRectAndPolygon() {
    double deltaX = center.x - m_width / 2;
    double deltaY = center.y - m_height / 2;
    int pixelDelta = m_pixelSize / 2;

    m_rect.x = deltaX;
    m_rect.y = deltaY;
    positionDisplayPolygon(deltaX - pixelDelta, deltaY - pixelDelta);
}

bool Enemy::isVisible() {
    return (center.x > minPosX && center.x < maxPosX && center.y > minPosY && center.y < maxPosY);
}

bool Enemy::isShooter() {
    return shooter;
}

void Enemy::applyVelocity() {
    center += m_velocity;
}
