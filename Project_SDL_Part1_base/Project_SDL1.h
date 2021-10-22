// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>


// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:

SDL_Renderer* window_renderer_ptr_;
SDL_Texture* animal_text = NULL;
SDL_Rect animal_rect;
float direction;
int count = 0;  

public:
  
  animal(const std::string& file_path, SDL_Renderer* window_renderer_ptr);

  ~animal(){
  // todo: Use the destructor to release memory and "clean up
  // behind you"
  SDL_DestroyTexture(this->animal_text); 
  };

  SDL_Texture* const getAnimalText(){
    return this->animal_text;
  }

  SDL_Rect const getAnimalRect(){
    return this->animal_rect;
  }

  int const getCount()
  {
    return this.count;
  }

  void setCount(int count)
  {
    this.count = count;
  }

  float getDirection()
  {
    return this.direction;
  }

  void setDirection(flaot direction)
  {
    this.direction = direction;
  }

  SDL_rect getAnimal_Rect()
  {
    return this.animal_rect;
  }

  void setAniaml_Rect(int x, int y)
  {
    this.animal_rect.x = x;
    this.animal_rect.y = y;
  }

  void draw(); // todo: Draw the animal on the screen <-> window_renderer_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

  virtual void move() = 0; // todo: Animals move around, but in a different
                             //fashion depending on which type of animal
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
  public:
  sheep(SDL_Renderer* window_renderer_ptr_);
  ~sheep();

  void move() override;
  };


// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

class wolf : public animal {
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
  public:
  wolf(SDL_Renderer* window_renderer_ptr_);
  ~wolf();
  void move() override;
  };

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {

private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Renderer* window_renderer_ptr_;
  std::vector<animal*> ListAnimal;
  SDL_Rect background;
  int counter = 0;
  // Some attribute to store all the wolves and sheep
  // here

public:
  //void AjouterDesAnimaux(std::)
  ground(SDL_Renderer* window_renderer_ptr); // todo: Ctor
  ~ground() = default; // todo: Dtor, again for clean up (if necessary)

  //void add_animal(some argument here); // todo: Add an animal
  void add_animal(animal* animal);


  void update(); // todo: "refresh the screen": Move animals and draw them
  // Possibly other methods, depends on your implementation
};

// The application class, which is in charge of generating the window
class application{
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_ = NULL;
  SDL_Renderer* window_renderer_ptr_ = NULL;
  SDL_Event window_event_;

  // Other attributes here, for example an instance of ground
  ground* groundApp = NULL;

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};