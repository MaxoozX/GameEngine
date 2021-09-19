#include <cstdlib>
#include <cmath> // Need to compile with -lm
#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // To load the texture (IMG_...)

#include "SpaceShooter.hpp"

using namespace std;

int main(int argc, char **argv) {

  SpaceShooter game(650, 1000, 60);
  game.setup();
  game.start();
  game.destroy();

  return 0;
}

/*
- Add a score counter
- Add some sort of super attack
- Add sounds with SDL_Mixer
*/