#include "renderer.h"
#include "theme.h"
#include <SDL.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    return 1;

  init_theme();

  SDL_Window *window = SDL_CreateWindow(
      "BC03", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      current_theme.screen_w, current_theme.screen_h, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    SDL_Log("Could not create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL) {
    SDL_Log("Could not create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_GameController *controller = NULL;
  for (int i = 0; i < SDL_NumJoysticks(); ++i) {
    if (SDL_IsGameController(i)) {
      controller = SDL_GameControllerOpen(i);
      if (controller) {
        SDL_Log("Opened gamecontroller %d: %s", i,
                SDL_GameControllerName(controller));
        break;
      } else {
        SDL_Log("Could not open gamecontroller %d: %s", i, SDL_GetError());
      }
    }
  }

  bool running = true;
  SDL_Event e;
  int cx = current_theme.screen_w / 2;
  int cy = current_theme.screen_h / 2;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) {
          cycle_theme();
        } else {
          running = false;
        }
      } else if (e.type == SDL_JOYBUTTONDOWN) {
        if (e.jbutton.button == 0) {
          cycle_theme();
        } else {
          running = false;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, current_theme.bg_color.r,
                           current_theme.bg_color.g, current_theme.bg_color.b,
                           255);
    SDL_RenderClear(renderer);

    render_face(renderer, cx, cy);
    render_hands(renderer, cx, cy);

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  if (controller) {
    SDL_GameControllerClose(controller);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
