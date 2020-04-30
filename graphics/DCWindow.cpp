// voxparser
// Created by Igor Frank on 30.04.20.
//

#include "DCWindow.h"
#include <Camera.h>
#include <SDL2CPP/MainLoop.h>

DCWindow::DCWindow(Camera &camera, unsigned int width, unsigned int height) : camera(camera), width(width), height(height) {}

void DCWindow::init() {
  mainLoop = std::make_shared<sdl2cpp::MainLoop>();
  mainLoop->setEventHandler(std::bind(&DCWindow::SDLHandler, this, std::placeholders::_1));
  if (width == 0 || height == 0) {
    getWindowSize();
  }
  window = std::make_shared<sdl2cpp::Window>(width, height);
  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);
}

void DCWindow::getWindowSize() {
  SDL_DisplayMode DM;
  if (SDL_GetDesktopDisplayMode(0, &DM) != 0) {
    throw std::runtime_error("SDL_GetDesktopDisplayMode failed");
  }
  width = static_cast<unsigned int>(DM.w * 0.8);
  height = static_cast<unsigned int>(DM.h * 0.8);
}

bool DCWindow::SDLHandler(const SDL_Event &event) {
  static bool mousePressed = false;
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
    case SDLK_w:
      camera.ProcessKeyboard(Camera_Movement::FORWARD, 0.1);
      return true;
    case SDLK_DOWN:
    case SDLK_s:
      camera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.1);
      return true;
    case SDLK_LEFT:
    case SDLK_a:
      camera.ProcessKeyboard(Camera_Movement::LEFT, 0.1);
      return true;
    case SDLK_RIGHT:
    case SDLK_d:
      camera.ProcessKeyboard(Camera_Movement::RIGHT, 0.1);
      return true;
    default:
      return false;
    }
  } else if (event.type == SDL_MOUSEBUTTONDOWN and event.button.button == SDL_BUTTON_LEFT) {
    mousePressed = true;
    return true;
  } else if (event.type == SDL_MOUSEMOTION and mousePressed) {
    camera.ProcessMouseMovement(-event.motion.xrel, event.motion.yrel);
    return true;
  } else if (event.type == SDL_MOUSEBUTTONUP and event.button.button == SDL_BUTTON_LEFT) {
    mousePressed = false;
    return true;
  }
  return false;
}

void DCWindow::setLoopCallback(const std::function<void(void)> &F) {
  mainLoop->setIdleCallback([=]() {
    F();
    window->swap();
  });
}

unsigned int DCWindow::getWidth() const { return width; }
unsigned int DCWindow::getHeight() const { return height; }

void DCWindow::operator()() { (*mainLoop)(); }
