#include <stdlib.h>
#include <math.h>
#include "../LinAlg/linalg.h" //needs to be updated when makefile is created

#define V_S 343.0 //speed of sound in air in m/s - update later

typedef struct 
{
    float x, y ,z;
} Point;


void calculate_tdoas(float* toas, float* tdoa_results, int num_toas){
    tdoa_results[0] = 0.0;
    for(int i = 1; i < num_toas; i++){
        tdoa_results[i] = toas[i] - toas[0];
    }
}

float calculate_distancesq_from_origin(Point point){
    return powf(point.x, 2) + powf(point.y, 2) + powf(point.z, 2);
}

//B will be used to output the B matrix in Ax = B
SquareMatrix form_matrix_system(float* tdoas, Point* receiver_coords, float* B){
    double** matrix_els = malloc(3 * sizeof(double*));

    float scaling_coeff = 2.0/V_S;

    float x1_scaled = receiver_coords[1].x/tdoas[1], y1_scaled = receiver_coords[1].y/tdoas[1], z1_scaled = receiver_coords[1].z/tdoas[1];
    float dist1_sq_scaled = calculate_distancesq_from_origin(receiver_coords[1])/tdoas[1];
    float disti_sq_scaled = 0.0;

    for(int i = 2; i < 5; i++){
        matrix_els[i-2] = malloc(3 * sizeof(double));

        matrix_els[i-2][0] = scaling_coeff * (x1_scaled - (receiver_coords[i].x/tdoas[i])); //x_i coefficient
        matrix_els[i-2][1] = scaling_coeff * (y1_scaled - (receiver_coords[i].y/tdoas[i])); //y_i coefficient
        matrix_els[i-2][2] = scaling_coeff * (z1_scaled - (receiver_coords[i].z/tdoas[i])); //z_i coefficient

        disti_sq_scaled = calculate_distancesq_from_origin(receiver_coords[i])/tdoas[i];
        B[i-2] = V_S * (tdoas[i] - tdoas[1]) + (dist1_sq_scaled - disti_sq_scaled)/V_S;        
    }

    SquareMatrix matrix_system = init_square_matrix(3, matrix_els);

    deinit_double_array(matrix_els, 3);

    return matrix_system;

}

//TODO: code to select which receiver's TOAs to use and use above functions + cramer_solve to find position
