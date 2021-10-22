#include "Project_SDL1.h"

#include <vector>
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

ground::ground(SDL_Renderer* window_renderer_ptr_)
{
  this->window_renderer_ptr_ = window_renderer_ptr_;
  // this->background_=background_;

}

void ground::add_animal(animal* animal)
  {
    this->ListAnimal.push_back(animal);
  };

void ground::update() // Fonction update Animaux
{
  for(auto animal : this->ListAnimal)
  {
    animal->move();
  }
}

application::application(unsigned n_sheep, unsigned n_wolf) // config de la fenetre
{
  SDL_CreateWindowAndRenderer(frame_width, frame_height, 0, &this->window_ptr_, &this->window_renderer_ptr_);
  SDL_SetRenderDrawColor(this->window_renderer_ptr_, 255, 255, 91, 100);
  SDL_Rect background = { 0, 0, frame_width, frame_height};
  SDL_RenderFillRect(this->window_renderer_ptr_, &background);

  this->groundApp = new ground(this->window_renderer_ptr_);

  for (unsigned i = 0; i < n_sheep;i++)
  {
    this->groundApp->add_animal(new sheep(this->window_renderer_ptr_));
  }

  for (unsigned j = 0; j < n_wolf; j++)
     this->groundApp->add_animal(new wolf(this->window_renderer_ptr_));

  SDL_RenderPresent(this->window_renderer_ptr_); // equivalent a SDL_Update
}


int application::loop(unsigned period)
{
  period = period * 1000; // Conversion des secondes en tick

  while(SDL_GetTicks() < period)
  {
    this->groundApp->update();
    SDL_Delay(frame_time);
    SDL_RenderPresent(this->window_renderer_ptr_);
  }
  return 1;
}

application::~application()
{
  SDL_DestroyRenderer(this->window_renderer_ptr_);
  SDL_DestroyWindow(this->window_ptr_);
}

animal::animal(const std::string& file_path, SDL_Renderer* window_renderer_ptr) {
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
    this->animal_text = load_texture_for(file_path, window_renderer_ptr);
    SDL_QueryTexture(this->animal_text, NULL, NULL, &this->animal_rect.w, &this->animal_rect.h);

    this->animal_rect.x = get_random_int_in_range(frame_boundary, frame_width - frame_boundary);
    this->animal_rect.y = get_random_int_in_range(frame_boundary, frame_height - frame_boundary);
  };


sheep::sheep(SDL_Renderer* window_renderer_ptr_):animal("../media/sheep.png",window_renderer_ptr_)
{
  SDL_Rect rect = this->getAnimalRect();
  this->setWindow_renderer_ptr(window_renderer_ptr_);
  SDL_RenderCopy(window_renderer_ptr_, this->getAnimalText(), NULL, &rect);
}

void sheep::move()
{
  SDL_Rect rect = this->getAnimalRect();

  if (rect.x + frame_boundary >= frame_width)
    this->set_r(false);
  else if (rect.x - frame_boundary + rect.w <= 0)
    this->set_r(true);

  if (rect.y + frame_boundary >= frame_height)
    this->set_d(false);
  else if (rect.y - frame_boundary + rect.h <= 0)
    this->set_d(true);

  if (this->get_r())
    rect.x += 1;
  else
    rect.x -= 1;

  if(this->get_d())
    rect.y += 1;
  else
    rect.y -= 1;

  this->setAnimalRect(rect);
  SDL_RenderCopy(this->getWindow_renderer_ptr(), this->getAnimalText(), NULL, &rect);

}


sheep::~sheep() = default;

wolf::wolf(SDL_Renderer* window_renderer_ptr_):animal("../media/wolf.png",window_renderer_ptr_)
{
  SDL_Rect rect = this->getAnimalRect();
  this->setWindow_renderer_ptr(window_renderer_ptr_);
  SDL_RenderCopy(window_renderer_ptr_, this->getAnimalText(), NULL, &rect);
}


void wolf::move()
{
  SDL_Rect rect = this->getAnimalRect();

  if (rect.x + frame_boundary >= frame_width)
    this->set_r(false);
  else if (rect.x - frame_boundary + rect.w <= 0)
    this->set_r(true);

  if (rect.y + frame_boundary >= frame_height)
    this->set_d(false);
  else if (rect.y - frame_boundary + rect.h <= 0)
    this->set_d(true);

  if (this->get_r())
    rect.x += 1;
  else
    rect.x -= 1;

  if(this->get_d())
    rect.y += 1;
  else
    rect.y -= 1;

  this->setAnimalRect(rect);
  SDL_RenderCopy(this->getWindow_renderer_ptr(), this->getAnimalText(), NULL, &rect);
}

wolf::~wolf() = default;

