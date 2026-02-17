#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>

typedef struct {
  float x;
  float y;
} Pointf;

Pointf rotate_point(Pointf p, float angle_deg);

#endif // GEOMETRY_H
