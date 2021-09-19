/**
 * Header file for Missile class.
 * @file Missile.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef MISSILE_H
#define MISSILE_H

#include <SDL2/SDL.h>

#include "Geometry.hpp"

#include "Sprite.hpp"

class Missile : public Sprite {
    private:
        int m_windowWidth;
        int m_windowHeight;
        int minPosX;
        int maxPosX;
        int minPosY;
        int maxPosY;
        bool fromPlayer;
        Geometry::Vector2d<double> m_velocity;

    public:
        Missile(SDL_Renderer* = nullptr, int = 0, int = 0, int = 0, int = 0, float = 0, float = 0, bool = false);
        void load();
        void updateRectAndPolygon();
        bool isVisible();
        bool isFromPlayer();
        void applyVelocity();
};

#endif // MISSILE_H