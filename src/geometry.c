#include "geometry.h"

float calculate_distancesq_from_origin(Point point){
    return powf(point.x, 2) + powf(point.y, 2) + powf(point.z, 2);
}
