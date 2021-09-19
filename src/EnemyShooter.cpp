/**
 * Implementation file for EnemyShooter class.
 * @file Enemy.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>

#include "EnemyShooter.hpp"
#include "Enemy.hpp"

EnemyShooter::EnemyShooter(SDL_Renderer* renderer,int windowWidth, int windowHeight, int x, int y, float velocityX, float velocityY): Enemy::Enemy(renderer, windowWidth, windowHeight, x, y, velocityX, velocityY, true) {}
