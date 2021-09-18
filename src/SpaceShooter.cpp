/**
 * implementation file for SpaceShooter class.
 * @file SpaceShooter.cpp
 * @author Maxence
 * @version 1.0
*/

#define SPEED 5

#include <SDL2/SDL.h>

#include "Game.hpp"
#include "SpaceShooter.hpp"
#include "Player.hpp"


SpaceShooter::SpaceShooter(int windowWidth, int windowHeight, int frameRate): Game::Game(windowWidth, windowHeight, frameRate), m_player(nullptr, windowWidth, windowHeight), leftArrowPressed(false), rightArrowPressed(false) {}

void SpaceShooter::setup() {
    Game::setup();
    m_player.m_renderer = m_renderer;
    m_player.load();
}

void SpaceShooter::update() {

    if(leftArrowPressed) {
        m_player.left();
    }

    if(rightArrowPressed) {
        m_player.right();
    }

    m_player.updateRectAndPolygon();

    SDL_Log("%f %f", m_player.m_x, m_player.m_y);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 1);
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 1);
    SDL_RenderDrawRect(m_renderer, &m_player.m_rect);
    drawTexture(m_player.m_texture, nullptr, &m_player.m_rect);

    m_player.displayPolygon.computeSidesAndDiagonals();
    for(auto side: m_player.displayPolygon.sides) {
        SDL_RenderDrawLine(m_renderer, side.first.x, side.first.y, side.second.x, side.second.y);
    }
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

                default:
                    break;
                }
            }
            break;

        default:
            break;
    }
}