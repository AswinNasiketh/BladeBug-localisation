#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>

#define V_S 343.0 //speed of sound in air in m/s - update later

typedef struct 
{
    float x, y ,z;
} Point;


float calculate_distancesq_from_origin(Point point);

#endif
