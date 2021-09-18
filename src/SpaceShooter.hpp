/**
 * Header file for SpaceShooter class.
 * @file SpaceShooter.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SPACESHOOTER_H
#define SPACESHOOTER_H

#include "Game.hpp"
#include "Player.hpp"

class SpaceShooter : public Game {
    private:

        Player m_player;

        bool leftArrowPressed;
        bool rightArrowPressed;

        void handleInput(const SDL_Event&);

    public:
        SpaceShooter(int = 0, int = 0, int = 30);
        void setup();
        void update();
};

#endif // SPACESHOOTER_H