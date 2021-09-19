/**
 * Implementation file for Player class.
 * @file Player.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>

#include "Player.hpp"
#include "Sprite.hpp"

#define LATERAL_SPEED 8

Player::Player(SDL_Renderer* renderer,int windowWidth, int windowHeight): Sprite::Sprite(325, 900, 160, 160, renderer, 10), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_health(100), maxHealth(100) {
    minPosX = m_width / 2;
    maxPosX = m_windowWidth - m_width / 2;
}

void Player::load() {
    Sprite::load("assets/player-polygon.png", "assets/player-texture.png");
}

void Player::left() {
    center.x -= LATERAL_SPEED;
    if(center.x < minPosX) {
        center.x = minPosX;
    }
}

void Player::right() {
    center.x += LATERAL_SPEED;
    if(center.x > maxPosX) {
        center.x = maxPosX;
    }
}

void Player::updateRectAndPolygon() {
    double deltaX = center.x - m_width / 2;
    double deltaY = center.y - m_height / 2;
    int pixelDelta = m_pixelSize / 2;

    m_rect.x = deltaX;
    m_rect.y = deltaY;
    positionDisplayPolygon(deltaX + pixelDelta, deltaY + pixelDelta);
}

void Player::heal(int amount) {
    m_health += amount;
    if(m_health > maxHealth) {
        m_health = maxHealth;
    }
}

void Player::damage(int amount) {
    m_health -= amount;
    if(m_health < 0) {
        m_health = 0;
    }
}

int Player::getHealth() const {
    return m_health;
}
