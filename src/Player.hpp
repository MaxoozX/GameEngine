/**
 * Header file for Player class.
 * @file Player.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "Sprite.hpp"

class Player : public Sprite {
    private:
        int m_windowWidth;
        int m_windowHeight;
        int minPosX;
        int maxPosX;

    public:
        Player(SDL_Renderer* = nullptr, int = 0, int = 0);
        void load();
        void left();
        void right();
        void updateRectAndPolygon();
};

#endif // PLAYER_H