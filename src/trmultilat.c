#include <stdlib.h>
#include <math.h>
#include "linalg.h" //needs to be updated when makefile is created
#include "geometry.h"

#define V_S 343.0 //speed of sound in air in m/s - update later
// matrix_t is the data type for elements in the matrix structure. Can be either double or float


SquareMatrix form_matrix_system( Point* receiver, matrix_t* ri){ // ri array being distance between rxi and bug
    matrix_t** matrix_els = malloc(3 * sizeof(matrix_t*));

    matrix_t* Ri_sq = malloc(4 * sizeof(matrix_t)); //Ri_sq being an array of distance between rxi and origin squared
    
    Ri_sq[0] = 0;
    Ri_sq[1] = calculate_distancesq_from_origin(receiver[1]);
    Ri_sq[2] = calculate_distancesq_from_origin(receiver[2]);
    Ri_sq[3] = calculate_distancesq_from_origin(receiver[3]);
    matrix_t r0_sq = ri[0] * ri[0];

    matrix_t* B = malloc(4 * sizeof(matrix_t));

    // 2x(-xi) + 2y(-yi) + 2z(-zi) = -Ri^2 + ri^2 - r0^2
    for(int i = 0; i < 3; i++){
        matrix_els[i] = malloc(3 * sizeof(matrix_t));

        //the equation start with point 1 instead of point 0
        matrix_els[i][0] = -2*receiver[i+1].x; //x
        matrix_els[i][1] = -2*receiver[i+1].y; //y
        matrix_els[i][2] = -2*receiver[i+1].z; //z

        B[i] = -Ri_sq[i+1] + (ri[i+1] * ri[i+1]) - r0_sq; 
    }

    SquareMatrix matrix_system = init_square_matrix(3, matrix_els);

    deinit_matrix_array(matrix_els, 3); //free matrix_els
    free(Ri_sq);

    return matrix_system;
}
