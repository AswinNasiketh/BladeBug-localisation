#ifndef PRMULTILAT_H
#define PRMULTILAT_H

#include "linalg.h"
#include "geometry.h"

matrix_t calculate_distancesq_from_origin(Point point);
SquareMatrix form_matrix_system( Point* receiver, matrix_t* ri, matrix_t* B);

#endif