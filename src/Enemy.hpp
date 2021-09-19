/**
 * Header file for Enemy class.
 * @file Enemy.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "Geometry.hpp"

#include "Sprite.hpp"

class Enemy : public Sprite {
    private:
        int m_windowWidth;
        int m_windowHeight;
        int minPosX;
        int maxPosX;
        int minPosY;
        int maxPosY;
        bool shooter;
        Geometry::Vector2d<double> m_velocity;

    public:
        Enemy(SDL_Renderer* = nullptr, int = 0, int = 0, int = 0, int = 0, float = 0, float = 0, bool = false);
        void load();
        void updateRectAndPolygon();
        bool isVisible();
        bool isShooter();
        void applyVelocity();
};

#endif // ENEMY_H