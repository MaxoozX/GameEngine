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

  SpaceShooter game(650, 1000, 30);
  game.setup();
  game.start();
  game.destroy();

  return 0;
}

/*
- Create the missile class
- Implement throwing missiles
- Create the enemty ship class
- Create a spawning function
- Put everything into a big vector for actualization
- Add sounds with SDL_Mixer
*/