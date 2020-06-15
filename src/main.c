#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "trmultilat.h"
#include "linalg.h"


int main(){   

    printf("Hello!\n");

    Point rx_positions[4];
    rx_positions[0] = (Point) {.x = 0, .y = 0, .z = 0};
    rx_positions[1] = (Point) {.x = 1, .y = 1, .z = 0};
    rx_positions[2] = (Point) {.x = 1, .y = 2, .z = 1};
    rx_positions[3] = (Point) {.x = 2, .y = 3, .z = 0};

    matrix_t measured_distances[] = {
        3.74f,
        3.16f,
        2.0f,
        3.32f
    };

    matrix_t *B = malloc(3 * sizeof(matrix_t)), *coords = malloc(3 * sizeof(matrix_t));

    SquareMatrix A = form_matrix_system(rx_positions, measured_distances, B);

    for(int i = 0; i < 3; i++){
        printf("\n");
        for(int j = 0; j < 3; j++){
            printf("%f", A.els[i][j]);
        }
    }

    printf("\n");

    cramer_solve(A, B, coords);

    printf("x = %f, y = %f, z = %f", coords[0], coords[1], coords[2]);

    free(B);

    return 0;
}