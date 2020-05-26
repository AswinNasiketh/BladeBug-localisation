#ifndef LINALG_H
#define LINALG_H



typedef struct{
    int n;
    double** els;
} SquareMatrix;


SquareMatrix init_square_matrix(int n, double** els);
SquareMatrix copy_square_matrix(SquareMatrix src);
void deinit_double_array(double** els, int n);
void deinit_square_matrix (SquareMatrix A);
double determinant(SquareMatrix mat);
void cramer_solve(SquareMatrix A, double* B, double* result);

#endif