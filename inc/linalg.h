#ifndef LINALG_H
#define LINALG_H

typedef float matrix_t;

typedef struct{
    int n;
    matrix_t** els;
} SquareMatrix;


SquareMatrix init_square_matrix(int n, matrix_t** els);
SquareMatrix copy_square_matrix(SquareMatrix src);
void deinit_matrix_array(matrix_t** els, int n);
void deinit_square_matrix (SquareMatrix A);
matrix_t determinant(SquareMatrix mat);
void cramer_solve(SquareMatrix A, matrix_t* B, matrix_t* result);

#endif