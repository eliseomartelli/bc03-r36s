#include "geometry.h"
#include <math.h>

Pointf rotate_point(Pointf p, float angle_deg) {
  float rad = angle_deg * (M_PI / 180.0f);
  return (Pointf){p.x * cosf(rad) - p.y * sinf(rad),
                  p.x * sinf(rad) + p.y * cosf(rad)};
}
