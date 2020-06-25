#ifndef PRMULTILAT_H
#define PRMULTILAT_H

#include "linalg.h"
#include "geometry.h"

void calculate_tdoas(float* toas, float* tdoa_results, int num_toas);
SquareMatrix prmultilat_form_matrix_system(float* tdoas, Point* receiver_coords, float* B);

#endif