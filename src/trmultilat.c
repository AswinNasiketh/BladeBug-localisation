#include <stdlib.h>
#include <math.h>
#include "linalg.h" //needs to be updated when makefile is created

#define V_S 343.0 //speed of sound in air in m/s - update later

typedef struct 
{
    float x, y ,z;
} Point;


// void calculate_tdoas(float* toas, float* tdoa_results, int num_toas){
//     tdoa_results[0] = 0.0;
//     for(int i = 1; i < num_toas; i++){
//         tdoa_results[i] = toas[i] - toas[0];
//     }
// }

float calculate_distancesq_from_origin(Point point){
    return powf(point.x, 2) + powf(point.y, 2) + powf(point.z, 2);
}

SquareMatrix form_matrix_system( Point** receiver, double* ri){ // ri array being distance between rxi and bug
    double** matrix_els = malloc(3 * sizeof(double*));

    double* Ri_sq = malloc(4 * sizeof(double)); //Ri_sq being an array of distance between rxi and origin squared
    
    Ri_sq[0] = 0;
    Ri_sq[1] = calculate_distancesq_from_origin(receiver[1]);
    Ri_sq[2] = calculate_distancesq_from_origin(receiver[2]);
    Ri_sq[3] = calculate_distancesq_from_origin(receiver[3]);

    r0_sq = pow(r[0], 2);



    for(int i = 0; i < 3; i++){

        matrix_els[i] = malloc(3 * sizeof(double));

        matrix_els[i][0] = -2*receiver[i].x //x
        matrix_els[i][1] = -2*receiver[i].y //y
        matrix_els[i][2] = -2*receiver[i].z //z

        
        B[i] = -Ri_sq[i] + pow(ri[i],2) - r0_sq; 
    }

    SquareMatrix matrix_system = init_square_matrix(3, matrix_els);

    deinit_double_array(matrix_els, 3);

    return matrix_system;

}
