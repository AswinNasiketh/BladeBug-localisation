#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>

#define N 3

int main(){

    printf("Hello!\n");

    matrix_t A[N][N] = {
        {-1.0, -5.0, -5.0},
        {4.0,-5.0, 4.0},
        {1.0,5.0, -1}
    };

    matrix_t** aPointer = malloc(N * sizeof(matrix_t*));


    for(int i = 0; i < N; i++){
        aPointer[i] = malloc(N * sizeof(matrix_t));
        for(int j = 0; j < N; j++){
            aPointer[i][j] = A[i][j];
        }
    }    

    matrix_t B[N] = {2.0, 19.0, -20.0};

    matrix_t result[N];

    SquareMatrix aMat = init_square_matrix(N, aPointer);
    cramer_solve(aMat, B, result);

    printf("x = %f and y = %f and z = %f\n", result[0], result[1], result[2]);

    deinit_square_matrix(aMat);

    return 0;
}