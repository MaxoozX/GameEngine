/**
 * implementation file for SpaceShooter class.
 * @file SpaceShooter.cpp
 * @author Maxence
 * @version 1.0
*/

#define SPEED 5

#include <random>

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"
#include "SpaceShooter.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"
#include "EnemyShooter.hpp"


SpaceShooter::SpaceShooter(int windowWidth, int windowHeight, int frameRate): Game::Game(windowWidth, windowHeight, frameRate), m_player(nullptr, windowWidth, windowHeight), leftArrowPressed(false), rightArrowPressed(false), spaceBarPressed(false), framesSinceLastMissile(0), defaultMissileVelocity(-300/frameRate), timeBetweenMissiles(frameRate/2), framesSinceLastEnemy(0), defaultEnemyVelocity(-300/frameRate), timeBetweenEnemies(frameRate/2), framesSinceLastEnemyShooter(0), defaultEnemyShooterVelocity(-200/frameRate), timeBetweenEnemyShooters(frameRate) {}

void SpaceShooter::setup() {
    Game::setup();

    m_player.setRenderer(m_renderer);
    m_player.load();

    missileTexture = IMG_LoadTexture(m_renderer, "assets/missile-texture.png");
    if(missileTexture == nullptr) {
        SDL_Log("Unable to load missiles texture");
    }
    missilePolygon = Geometry::getPolygonFromPNG<int>("assets/missile-polygon.png");
    missilePolygon.computeMidPoint();
    double scaleFactorX = 20 / missilePolygon.m_w;
    double scaleFactorY = 30 / missilePolygon.m_h;
    for(auto &vertex : missilePolygon.vertices) {
        vertex.x *= scaleFactorX;
        vertex.y *= scaleFactorY;
    }
    missilePolygon.m_w = 20;
    missilePolygon.m_h = 30;

    enemyTexture = IMG_LoadTexture(m_renderer, "assets/enemy-texture.png");
    if(enemyTexture == nullptr) {
        SDL_Log("Unable to load enemy texture");
    }
    enemyPolygon = Geometry::getPolygonFromPNG<int>("assets/enemy-polygon.png");
    enemyPolygon.computeMidPoint();
    scaleFactorX = 80 / enemyPolygon.m_w;
    scaleFactorY = 80 / enemyPolygon.m_h;
    for(auto &vertex : enemyPolygon.vertices) {
        vertex.x *= scaleFactorX;
        vertex.y *= scaleFactorY;
    }
    for(auto &vertex : enemyPolygon.vertices) {
        vertex.x = 80 - vertex.x;
        vertex.y = 80 - vertex.y;
    }
    enemyPolygon.m_w = 80;
    enemyPolygon.m_h = 80;

    enemyShooterTexture = IMG_LoadTexture(m_renderer, "assets/enemy-shooter-texture.png");
    if(enemyShooterTexture == nullptr) {
        SDL_Log("Unable to load enemy shooter texture");
    }
    enemyShooterPolygon = Geometry::getPolygonFromPNG<int>("assets/enemy-shooter-polygon.png");
    enemyShooterPolygon.computeMidPoint();
    scaleFactorX = 80 / enemyShooterPolygon.m_w;
    scaleFactorY = 80 / enemyShooterPolygon.m_h;
    for(auto &vertex : enemyShooterPolygon.vertices) {
        vertex.x *= scaleFactorX;
        vertex.y *= scaleFactorY;
    }
    for(auto &vertex : enemyShooterPolygon.vertices) {
        vertex.x = 80 - vertex.x;
        vertex.y = 80 - vertex.y;
    }
    enemyShooterPolygon.m_w = 80;
    enemyShooterPolygon.m_h = 80;
}

void SpaceShooter::update() {

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 1);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 1);

    if(leftArrowPressed) {
        m_player.left();
    }

    if(rightArrowPressed) {
        m_player.right();
    }

    if(spaceBarPressed) {
        SDL_Delay(3000);
    }

    if(framesSinceLastMissile >= timeBetweenMissiles) {
        fireMissile();
        framesSinceLastMissile = 0;
    }
    framesSinceLastMissile++;

    if(framesSinceLastEnemy >= timeBetweenEnemies) {
        if(dist(mt) < 25) {
            SDL_Log("HI");
            spawnEnemyShooter(80 + dist(mt)%390);
            framesSinceLastEnemy = 0;
        } else if(dist(mt) <= 67) {
            spawnEnemy(80 + dist(mt)%390);
            framesSinceLastEnemy = 0;
        }
    }
    framesSinceLastEnemy++;

    m_player.updateRectAndPolygon();
    m_player.displayPolygon.computeMidPoint();
    m_player.displayPolygon.computeSidesAndDiagonals();

    // Move the missiles
    for(int index = 0; index < missiles.size(); index++) {
        Missile* missile = missiles[index];
        missile->applyVelocity();
        if(!missile->isVisible()) {
            missiles.erase(missiles.begin()+index);
            delete missile;
            continue;
        }
        if(!missile->isFromPlayer()) {
            if(Sprite::doesRectanglesCollide(m_player.m_rect, missile->m_rect)) {
                std::pair<bool, Geometry::Point2d<int> *> collisionObject = Geometry::checkPolygonCollision<int>(m_player.displayPolygon, missile->displayPolygon);
                if(collisionObject.first) {
                    m_player.damage(2);
                    missiles.erase(missiles.begin() + index);
                    delete missile;
                    continue;
                }
            }
        }
        missile->updateRectAndPolygon();
        missile->displayPolygon.computeMidPoint();
        missile->displayPolygon.computeSidesAndDiagonals();
    }

    // Move the enemies
    for(int index = 0; index < enemies.size(); index++) {
        Enemy* enemy = enemies[index];
        enemy->applyVelocity();
        if(!enemy->isVisible()) {
            enemies.erase(enemies.begin()+index);
            delete enemy;
            enemy = nullptr;
            continue;
        }
        if(Sprite::doesRectanglesCollide(m_player.m_rect, enemy->m_rect)) {
            std::pair<bool, Geometry::Point2d<int> *> collisionObject = Geometry::checkPolygonCollision<int>(m_player.displayPolygon, enemy->displayPolygon);
            if(collisionObject.first) {
                m_player.damage(5);
                enemies.erase(enemies.begin() + index);
                delete enemy;
                continue;
            }
        }
        if(enemy->isShooter()) {
            if(dist(mt) <= 12 ) {
                spawnMissile(enemy->center.x, enemy->center.y + enemy->m_height, 0, -defaultMissileVelocity);
            }
        }
        enemy->updateRectAndPolygon();
        enemy->displayPolygon.computeMidPoint();
        enemy->displayPolygon.computeSidesAndDiagonals();
    }

    // Check for collision
    for(int indexEnemy = 0; indexEnemy < enemies.size(); indexEnemy++) {
        Enemy* enemy = enemies[indexEnemy];
        for(int indexMissile = 0; indexMissile < missiles.size(); indexMissile++) {
            Missile* missile = missiles[indexMissile];
            if(!missile->isFromPlayer()) continue;
            if(Sprite::doesRectanglesCollide(enemy->m_rect, missile->m_rect)) {
                std::pair<bool, Geometry::Point2d<int> *> collisionObject = Geometry::checkPolygonCollision<int>(enemy->displayPolygon, missile->displayPolygon);
                if(collisionObject.first) {
                    SDL_Log("collision");
                    enemies.erase(enemies.begin() + indexEnemy);
                    delete enemy;
                    missiles.erase(missiles.begin() + indexMissile);
                    delete missile;
                    continue;
                }
            }
        }
    }

    // Display
    for(int index = 0; index < missiles.size(); index++) {
        Missile* missile = missiles[index];
        drawTexture(missile->m_texture, nullptr, &missile->m_rect);
    }

    for(int index = 0; index < enemies.size(); index++) {
        Enemy* enemy = enemies[index];

        if(Sprite::doesRectanglesCollide(enemy->m_rect, m_player.m_rect)) {
            std::pair<bool, Geometry::Point2d<int> *> collisionObject = Geometry::checkPolygonCollision<int>(enemy->displayPolygon, m_player.displayPolygon);
            if(collisionObject.first) {
                SDL_Log("A enemy touched the player");
            }
        }
        
        drawTexture(enemy->m_texture, nullptr, &enemy->m_rect, 180.0);
    }

    // Draw the life
    drawTexture(m_player.m_texture, nullptr, &m_player.m_rect);

    SDL_Log("Health : %d", m_player.getHealth());
    SDL_Rect curHealthRect;
    SDL_Rect maxHealthRect;
    curHealthRect.y = (int)m_player.center.y + m_player.m_height / 2 + 5;
    maxHealthRect.y = (int)m_player.center.y + m_player.m_height / 2 + 5;
    curHealthRect.x = (int)m_player.center.x - 50;
    maxHealthRect.x = (int)m_player.center.x - 50;
    curHealthRect.h = 10;
    maxHealthRect.h = 10;
    curHealthRect.w = m_player.getHealth();
    maxHealthRect.w = 100;

    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 1);
    SDL_RenderFillRect(m_renderer, &maxHealthRect);
    SDL_SetRenderDrawColor(m_renderer, 0, 200, 0, 1);
    SDL_RenderFillRect(m_renderer, &curHealthRect);
}

void SpaceShooter::handleInput(const SDL_Event &event) {
    switch (event.type) {

        case SDL_KEYDOWN:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                    case SDLK_LEFT:
                        leftArrowPressed = true;
                        break;

                    case SDLK_RIGHT:
                        rightArrowPressed = true;
                        break;

                    case SDLK_SPACE:
                        spaceBarPressed = true;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SDL_KEYUP:
            if (event.key.repeat == 0) {
                switch (event.key.keysym.sym) {

                case SDLK_LEFT:
                    leftArrowPressed = false;
                    break;

                case SDLK_RIGHT:
                    rightArrowPressed = false;
                    break;

                case SDLK_SPACE:
                    spaceBarPressed = false;
                    break;

                default:
                    break;
                }
            }
            break;

        default:
            break;
    }
}

void SpaceShooter::fireMissile() {
    spawnMissile(m_player.center.x, m_player.center.y - m_player.m_width / 2, 0, defaultMissileVelocity, true);
}

void SpaceShooter::spawnMissile(int x, int y, int velocityX, int velocityY, bool isFromPlayer) {
    Missile* newMissile = new Missile(m_renderer, gameWindowWidth, gameWindowHeight, x, y, velocityX, velocityY, isFromPlayer);
    newMissile->setTexture(missileTexture);
    newMissile->setScaledPolygon(missilePolygon);
    missiles.push_back(newMissile);
}

void SpaceShooter::spawnEnemy(int x, int y) {
    Enemy* newEnemy = new Enemy(m_renderer, gameWindowWidth, gameWindowHeight, x, y, 0, 3);
    newEnemy->setTexture(enemyTexture);
    newEnemy->setScaledPolygon(enemyPolygon);
    enemies.push_back(newEnemy);
}

void SpaceShooter::spawnEnemyShooter(int x, int y) {
    EnemyShooter* newEnemy = new EnemyShooter(m_renderer, gameWindowWidth, gameWindowHeight, x, y, 0, 3);
    newEnemy->setTexture(enemyShooterTexture);
    newEnemy->setScaledPolygon(enemyShooterPolygon);
    enemies.push_back(newEnemy);
}
