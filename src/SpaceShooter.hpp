/**
 * Header file for SpaceShooter class.
 * @file SpaceShooter.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SPACESHOOTER_H
#define SPACESHOOTER_H

#include <vector>

#include <SDL2/SDL.h>

#include "Geometry.hpp"

#include "Game.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "EnemyShooter.hpp"

class SpaceShooter : public Game {
    private:

        Player m_player;

        // Missiles
        SDL_Texture* missileTexture;
        Geometry::Polygon<int> missilePolygon;
        std::vector<Missile*> missiles;
        int defaultMissileVelocity;
        int framesSinceLastMissile;
        int timeBetweenMissiles;

        // Enemys
        SDL_Texture* enemyTexture;
        Geometry::Polygon<int> enemyPolygon;
        std::vector<Enemy*> enemies;
        int defaultEnemyVelocity;
        int framesSinceLastEnemy;
        int timeBetweenEnemies;

        SDL_Texture* enemyShooterTexture;
        Geometry::Polygon<int> enemyShooterPolygon;
        std::vector<EnemyShooter*> enemyShooters;
        int defaultEnemyShooterVelocity;
        int framesSinceLastEnemyShooter;
        int timeBetweenEnemyShooters;


        bool leftArrowPressed;
        bool rightArrowPressed;
        bool spaceBarPressed;

        

        void handleInput(const SDL_Event&);
        void fireMissile();
        void spawnMissile(int = 0, int = 0, int = 0, int = 0, bool = false);
        void spawnEnemy(int = 100, int = 100);
        void spawnEnemyShooter(int = 100, int = 100);

    public:
        SpaceShooter(int = 0, int = 0, int = 30);
        void setup();
        void update();
};

#endif // SPACESHOOTER_H