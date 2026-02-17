#include "renderer.h"
#include "geometry.h"
#include "theme.h"
#include <SDL.h>
#include <stdbool.h>
#include <time.h>

void draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius) {
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
      }
    }
  }
}

void draw_rotated_rect(SDL_Renderer *renderer, int cx, int cy, float length,
                       float width, float angle, int offset_back) {
  float half_w = width / 2.0f;

  Pointf corners[4] = {{-half_w, (float)offset_back},
                       {half_w, (float)offset_back},
                       {half_w, -length},
                       {-half_w, -length}};

  SDL_Vertex vertices[4];
  SDL_Color c;
  SDL_GetRenderDrawColor(renderer, &c.r, &c.g, &c.b, &c.a);

  for (int i = 0; i < 4; i++) {
    Pointf rotated = rotate_point(corners[i], angle);
    vertices[i].position.x = cx + rotated.x;
    vertices[i].position.y = cy + rotated.y;
    vertices[i].color = c;
    vertices[i].tex_coord = (SDL_FPoint){0, 0};
  }

  int indices[6] = {0, 1, 2, 0, 2, 3};
  SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);
}

void render_face(SDL_Renderer *renderer, int cx, int cy) {
  SDL_SetRenderDrawColor(renderer, current_theme.bg_color.r,
                         current_theme.bg_color.g, current_theme.bg_color.b,
                         255);
  SDL_Rect case_rect = {cx - current_theme.case_size / 2,
                        cy - current_theme.case_size / 2,
                        current_theme.case_size, current_theme.case_size};
  SDL_RenderFillRect(renderer, &case_rect);

  SDL_SetRenderDrawColor(renderer, current_theme.face_color.r,
                         current_theme.face_color.g, current_theme.face_color.b,
                         255);
  draw_filled_circle(renderer, cx, cy, current_theme.clock_radius);

  SDL_SetRenderDrawColor(renderer, current_theme.tick_color.r,
                         current_theme.tick_color.g, current_theme.tick_color.b,
                         255);
  for (int i = 0; i < 60; i++) {
    bool is_hour = (i % 5 == 0);
    float tick_len = is_hour ? 15.0f : 8.0f;
    float tick_w = is_hour ? 4.0f : 1.0f;

    float angle = i * 6.0f;

    Pointf start = {0, (float)-current_theme.clock_radius};
    Pointf rot_start = rotate_point(start, angle);

    draw_rotated_rect(renderer, cx + rot_start.x, cy + rot_start.y, -tick_len,
                      tick_w, angle, 0);
  }
}

void render_hands(SDL_Renderer *renderer, int cx, int cy) {
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  float sec = timeinfo->tm_sec;
  float min = timeinfo->tm_min + (sec / 60.0f);
  float hr = timeinfo->tm_hour + (min / 60.0f);

  float ang_s = sec * 6.0f;
  float ang_m = min * 6.0f;
  float ang_h = (hr > 12 ? hr - 12 : hr) * 30.0f;

  SDL_SetRenderDrawColor(renderer, current_theme.hand_color.r,
                         current_theme.hand_color.g, current_theme.hand_color.b,
                         255);
  draw_rotated_rect(renderer, cx, cy,
                    current_theme.clock_radius * current_theme.h_len,
                    current_theme.h_width, ang_h, 0);

  draw_rotated_rect(renderer, cx, cy,
                    current_theme.clock_radius * current_theme.m_len,
                    current_theme.m_width, ang_m, 0);

  SDL_SetRenderDrawColor(renderer, current_theme.sec_hand_color.r,
                         current_theme.sec_hand_color.g,
                         current_theme.sec_hand_color.b, 255);
  draw_rotated_rect(renderer, cx, cy,
                    current_theme.clock_radius * current_theme.s_len,
                    current_theme.s_width, ang_s, 30);

  draw_filled_circle(renderer, cx, cy, 6);
}
