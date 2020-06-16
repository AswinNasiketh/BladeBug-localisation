#include "linalg.h"
#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#define TEST_TR_MULTILAT
// #define TEST_PR_MULTILAT

#ifdef TEST_TR_MULTILAT
#include "trmultilat.h"
#endif

#ifdef TEST_PR_MULTILAT
#include "prmultilat.h"
#endif

#ifdef TEST_TR_MULTILAT
void test_tr_multilat(void){
        printf("TR Multilateration Test!\n");

    Point rx_positions[4];
    rx_positions[0] = (Point) {.x = 0, .y = 0, .z = 0};
    rx_positions[1] = (Point) {.x = 2, .y = 10, .z = 1};
    rx_positions[2] = (Point) {.x = 7, .y = 2, .z = 0};
    rx_positions[3] = (Point) {.x = 10, .y = 6, .z = 8};

    matrix_t measured_distances[] = {
        8.77f,
        8.37f,
        6.63f,
        5.74f
    };

    matrix_t *B = malloc(3 * sizeof(matrix_t)), *coords = malloc(3 * sizeof(matrix_t));

    SquareMatrix A = form_matrix_system(rx_positions, measured_distances, B);

    // for(int i = 0; i < 3; i++){
    //     printf("\n");
    //     for(int j = 0; j < 3; j++){
    //         printf("%f", A.els[i][j]);
    //     }
    // }

    printf("\n");

    cramer_solve(A, B, coords);

    printf("x = %f, y = %f, z = %f", coords[0], coords[1], coords[2]);

    free(B);
}

#endif

#ifdef TEST_PR_MULTILAT
void test_pr_multilat(void){
    printf("PR Multilateration Test!\n");

    Point rx_positions[5];
    rx_positions[0] = (Point) {.x = 0, .y = 0, .z = 0};
    rx_positions[1] = (Point) {.x = 9, .y = 9, .z = 1};
    rx_positions[2] = (Point) {.x = 5, .y = 0, .z = 10};
    rx_positions[3] = (Point) {.x = 7, .y = 4, .z = 8};
    rx_positions[4] = (Point) {.x = 8, .y = 8, .z = 8};



    matrix_t measured_toas[] = {
        0.039006f,
        0.018438f,
        0.028266f,
        0.014866f,
        0.005050f
    };

    float* B = malloc(3 * sizeof(matrix_t)), *coords = malloc(3 * sizeof(matrix_t));

    float* tdoas = malloc(5 * sizeof(float));

    calculate_tdoas(measured_toas, tdoas, 5);

    SquareMatrix A = prmultilat_form_matrix_system(tdoas, rx_positions, B);

    // for(int i = 0; i < 3; i++){
    //     printf("\n");
    //     for(int j = 0; j < 3; j++){
    //         printf("%f", A.els[i][j]);
    //     }
    // }

    printf("\n");

    cramer_solve(A, B, coords);

    printf("x = %f, y = %f, z = %f", coords[0], coords[1], coords[2]);

    free(B);
}

#endif

int main(){   

    test_tr_multilat();
    // test_pr_multilat();

    return 0;
}