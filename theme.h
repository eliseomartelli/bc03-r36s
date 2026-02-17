#ifndef THEME_H
#define THEME_H

#include <SDL.h>

typedef struct {
  int screen_w;
  int screen_h;
  int clock_radius;
  int case_size;

  float h_len;
  int h_width;
  float m_len;
  int m_width;
  float s_len;
  int s_width;

  SDL_Color bg_color;
  SDL_Color face_color;
  SDL_Color tick_color;
  SDL_Color hand_color;
  SDL_Color sec_hand_color;
} Theme;

extern Theme current_theme;

void cycle_theme(void);
void init_theme(void);

#endif // THEME_H
