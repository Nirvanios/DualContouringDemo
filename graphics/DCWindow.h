//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_DCWINDOW_H
#define DUALCONTOURDEMO_DCWINDOW_H

#include <Camera.h>
#include <SDL2/include/SDL2/SDL_events.h>
#include <SDL2CPP/MainLoop.h>
#include <SDL2CPP/Window.h>
class DCWindow {
  using SDL2MainLoop = std::shared_ptr<sdl2cpp::MainLoop>;
  using SDL2Window = std::shared_ptr<sdl2cpp::Window>;

private:
  Camera &camera;
  unsigned int width = 0;
  unsigned int height = 0;
  SDL2MainLoop mainLoop;
  SDL2Window window;

  void getWindowSize();

public:
  DCWindow(Camera &camera, unsigned int width = 0, unsigned int height = 0);
  void init();

  bool SDLHandler(const SDL_Event &event);

  [[nodiscard]] unsigned int getWidth() const;
  [[nodiscard]] unsigned int getHeight() const;
  void setLoopCallback(const std::function<void(void)> &F);

  void operator()();
};

#endif // DUALCONTOURDEMO_DCWINDOW_H
