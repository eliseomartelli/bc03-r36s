#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

void draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius);
void draw_rotated_rect(SDL_Renderer *renderer, int cx, int cy, float length,
                       float width, float angle, int offset_back);
void render_face(SDL_Renderer *renderer, int cx, int cy);
void render_hands(SDL_Renderer *renderer, int cx, int cy);

#endif // RENDERER_H
