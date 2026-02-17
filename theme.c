#include "theme.h"
#include <SDL.h>

static const Theme themes[] = {
    {.screen_w = 640,
     .screen_h = 480,
     .clock_radius = 216,
     .case_size = 480,
     .h_len = 0.55f,
     .h_width = 10,
     .m_len = 0.80f,
     .m_width = 6,
     .s_len = 0.85f,
     .s_width = 3,
     .bg_color = {10, 10, 10, 255},
     .face_color = {30, 30, 30, 255},
     .tick_color = {200, 200, 200, 255},
     .hand_color = {255, 255, 255, 255},
     .sec_hand_color = {255, 204, 0, 255}},

    {.screen_w = 640,
     .screen_h = 480,
     .clock_radius = 216,
     .case_size = 480,
     .h_len = 0.55f,
     .h_width = 10,
     .m_len = 0.80f,
     .m_width = 6,
     .s_len = 0.85f,
     .s_width = 3,
     .bg_color = {220, 220, 220, 255},
     .face_color = {245, 245, 245, 255},
     .tick_color = {20, 20, 20, 255},
     .hand_color = {10, 10, 10, 255},
     .sec_hand_color = {255, 204, 0, 255}},

    {.screen_w = 640,
     .screen_h = 480,
     .clock_radius = 216,
     .case_size = 480,
     .h_len = 0.55f,
     .h_width = 10,
     .m_len = 0.80f,
     .m_width = 6,
     .s_len = 0.85f,
     .s_width = 3,
     .bg_color = {220, 220, 220, 255},
     .face_color = {30, 30, 30, 255},
     .tick_color = {255, 255, 255, 255},
     .hand_color = {255, 255, 255, 255},
     .sec_hand_color = {255, 204, 0, 255}},

    {.screen_w = 640,
     .screen_h = 480,
     .clock_radius = 216,
     .case_size = 480,
     .h_len = 0.55f,
     .h_width = 10,
     .m_len = 0.80f,
     .m_width = 6,
     .s_len = 0.85f,
     .s_width = 3,
     .bg_color = {10, 10, 10, 255},
     .face_color = {245, 245, 245, 255},
     .tick_color = {20, 20, 20, 255},
     .hand_color = {10, 10, 10, 255},
     .sec_hand_color = {255, 204, 0, 255}},
};

#define NUM_THEMES (sizeof(themes) / sizeof(themes[0]))

Theme current_theme;
static int current_theme_index = 0;

void init_theme(void) {
  current_theme_index = 1;
  current_theme = themes[current_theme_index];
}

void cycle_theme(void) {
  current_theme_index = (current_theme_index + 1) % NUM_THEMES;
  current_theme = themes[current_theme_index];
}
