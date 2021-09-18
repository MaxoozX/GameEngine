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

Player::Player(SDL_Renderer* renderer,int windowWidth, int windowHeight): Sprite::Sprite(325, 800, 160, 160, renderer, 10), m_windowWidth(windowWidth), m_windowHeight(windowHeight) {
    minPosX = m_width / 2;
    maxPosX = m_windowWidth - m_width / 2;
}

void Player::load() {
    Sprite::load("assets/player-polygon.png", "assets/player-texture.png");
}

void Player::left() {
    m_x -= LATERAL_SPEED;
    if(m_x < minPosX) {
        m_x = minPosX;
    }
}

void Player::right() {
    m_x += LATERAL_SPEED;
    if(m_x > maxPosX) {
        m_x = maxPosX;
    }
}

void Player::updateRectAndPolygon() {
    double deltaX = m_x - m_width / 2;
    double deltaY = m_y - m_height / 2;
    int pixelDelta = m_pixelSize / 2;

    m_rect.x = deltaX;
    m_rect.y = deltaY;
    positionDisplayPolygon(deltaX + pixelDelta, deltaY + pixelDelta);
}