#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Texture* load_texture_for(const std::string& path,
                              SDL_Renderer* renderer) {
  SDL_Texture* loaded_image = IMG_LoadTexture(renderer, path.c_str());

  if (loaded_image == nullptr) {
    throw std::runtime_error("Unable to load image");
  } 
  return loaded_image;
}

int get_random_int_in_range(int min, int max) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(min, max);
  return uni(rng);
}
}

application::application(unsigned n_sheep, unsigned n_wolf) // config de la fenetre
{
  SDL_CreateWindowAndRenderer(frame_width, frame_height, 0, &this->window_ptr_, &this->window_renderer_ptr_);
  SDL_SetRenderDrawColor(this->window_renderer_ptr_, 190, 255, 91, 100);
  SDL_Rect background = { 0, 0, frame_width, frame_height};
  SDL_RenderFillRect(this->window_renderer_ptr_, &background);

  for (unsigned i = 0; i < n_sheep;i++)
  {
    sheep newSheep(this->window_renderer_ptr_);
  }
  for (unsigned j = 0; j < n_wolf; j++)
    wolf neWolf(this->window_renderer_ptr_);

  SDL_RenderPresent(this->window_renderer_ptr_); // equivalent a lupdate

}

application::~application()
{
  SDL_DestroyRenderer(this->window_renderer_ptr_);
  SDL_DestroyWindow(this->window_ptr_);
}

sheep::sheep(SDL_Renderer* window_renderer_ptr_):animal("../media/sheep.png",window_renderer_ptr_)
{
  SDL_Rect rect = this->getAnimalRect();
  SDL_RenderCopy(window_renderer_ptr_, this->getAnimalText(), NULL, &rect);
}

sheep::~sheep() = default;

wolf::wolf(SDL_Renderer* window_renderer_ptr_):animal("../media/wolf.png",window_renderer_ptr_)
{
  SDL_Rect rect = this->getAnimalRect();
  SDL_RenderCopy(window_renderer_ptr_, this->getAnimalText(), NULL, &rect);
}

wolf::~wolf() = default;

animal::animal(const std::string& file_path, SDL_Renderer* window_renderer_ptr) {
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
    this->animal_text = load_texture_for(file_path, window_renderer_ptr);
    SDL_QueryTexture(this->animal_text, NULL, NULL, &this->animal_rect.w, &this->animal_rect.h);

    this->animal_rect.x = get_random_int_in_range(frame_boundary, frame_width - frame_boundary);
    this->animal_rect.y = get_random_int_in_range(frame_boundary, frame_height - frame_boundary);
  };

int application::loop(unsigned period)
{
  period = period * 1000; // Conversion des secondes en tick

  while(SDL_GetTicks() < period)
  {
    SDL_Delay(frame_time);
    SDL_RenderPresent(this->window_renderer_ptr_);
  }
  return 1;
}

// ground::ground(SDL_Renderer* window_renderer_ptr_)
// {
//   this->window_renderer_ptr_ = window_renderer_ptr_;;
//   this->background_=background_;
// }