/**
 * Header file for EnemyShooter class.
 * @file EnemyShooter.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include <SDL2/SDL.h>

#include "Geometry.hpp"

#include "Enemy.hpp"

class EnemyShooter : public Enemy {
    private:

    public:
        EnemyShooter(SDL_Renderer* = nullptr, int = 0, int = 0, int = 0, int = 0, float = 0, float = 0);
};

#endif // ENEMYSHOOTER_H