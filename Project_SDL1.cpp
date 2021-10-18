// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.

//

// dans objet animal == mettre frag du mouton 

#include "Project_SDL1.h"



#include <algorithm>

#include <cassert>

#include <cstdlib>

#include <numeric>

#include <random>

#include <string>

#include <SDL2/SDL_image.h>



void init() {

  // Initialize SDL

  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)

    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  SDL_Window *window = SDL_CreateWindow("SDL2 Window",

                                          SDL_WINDOWPOS_CENTERED,

                                          SDL_WINDOWPOS_CENTERED,

                                          1000, 1000,

                                          0);

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);

  SDL_Rect rect = {0, 0, 1000, 2000}; // x, y, width, height

  SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0x00, 0x5f, 0x00));





  // Initialize PNG loading

  int imgFlags = IMG_INIT_PNG;

  if (!(IMG_Init(imgFlags) & imgFlags))

    throw std::runtime_error("init(): SDL_image could not initialize! "

                             "SDL_image Error: " +

                             std::string(IMG_GetError()));

  SDL_UpdateWindowSurface(window);

}



namespace {

// Defining a namespace without a name -> Anonymous workspace

// Its purpose is to indicate to the compiler that everything

// inside of it is UNIQUELY used within this source file.



SDL_Surface* load_surface_for(const std::string& path,

                              SDL_Surface* window_surface_ptr) {



  // Helper function to load a png for a specific surface

  // See SDL_ConvertSurface

}

} // namespace


