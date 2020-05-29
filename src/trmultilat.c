#include <stdlib.h>
#include <math.h>
#include "linalg.h" //needs to be updated when makefile is created

#define V_S 343.0 //speed of sound in air in m/s - update later

typedef struct 
{
    float x, y ,z;
} Point;

float calculate_distancesq_from_origin(Point point){
    return powf(point.x, 2) + powf(point.y, 2) + powf(point.z, 2);
}

SquareMatrix form_matrix_system( Point* receiver, float* ri){ // ri array being distance between rxi and bug
    float** matrix_els = malloc(3 * sizeof(float*));

    float* Ri_sq = malloc(4 * sizeof(float)); //Ri_sq being an array of distance between rxi and origin squared
    
    Ri_sq[0] = 0;
    Ri_sq[1] = calculate_distancesq_from_origin(receiver[1]);
    Ri_sq[2] = calculate_distancesq_from_origin(receiver[2]);
    Ri_sq[3] = calculate_distancesq_from_origin(receiver[3]);
    float r0_sq = powf(r[0], 2);

    float B* = malloc(4 * sizeof(float));

    // 2x(-xi) + 2y(-yi) + 2z(-zi) = -Ri^2 + ri^2 - r0^2
    for(int i = 0; i < 3; i++){
        matrix_els[i] = malloc(3 * sizeof(float));

        //the equation start with point 1 instead of point 0
        matrix_els[i][0] = -2*receiver[i+1].x; //x
        matrix_els[i][1] = -2*receiver[i+1].y; //y
        matrix_els[i][2] = -2*receiver[i+1].z; //z

        B[i] = -Ri_sq[i+1] + pow(ri[i+1],2) - r0_sq; 
    }

    SquareMatrix matrix_system = init_square_matrix(3, matrix_els);

    deinit_float_array(matrix_els, 3); //free matrix_els
    free(Ri_sq);

    return matrix_system;
}
