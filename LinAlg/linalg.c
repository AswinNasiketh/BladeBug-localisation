#include <math.h>
#include <stdlib.h>
#include "linalg.h"

//first index is row, 2nd index is column

SquareMatrix init_square_matrix(int n, double** els){
    SquareMatrix newMat = {
        .n =n,
        .els = malloc(n * sizeof(double*))
    };

    for(int i = 0; i < n; i++){
        newMat.els[i] = malloc(n * sizeof(double));

        for(int j = 0; j < n; j++){
            newMat.els[i][j] = els[i][j];
        }
    }

    return newMat;
}

SquareMatrix copy_square_matrix(SquareMatrix src){
    SquareMatrix dest;
    dest.n = src.n;
    dest.els = malloc(dest.n * sizeof(double*));

    for(int i = 0; i < dest.n; i++){
        dest.els[i] = malloc(dest.n * sizeof(double));

        for(int j = 0; j < dest.n; j++){
            dest.els[i][j] = src.els[i][j];
        }
    }

    return dest;
}

void deinit_double_array(double** els, int n){
    for(int i = 0; i < n; i++){
        free(els[i]);
    }
    free(els);
}

void deinit_square_matrix (SquareMatrix A){
    deinit_double_array(A.els, A.n);
}

double determinant(SquareMatrix mat){
    double det = 0.0;
    double** subMatEls = malloc((mat.n-1) * sizeof(double*));
    for(int i = 0; i < mat.n - 1; i++) subMatEls[i] = malloc((mat.n - 1) * sizeof(double));
    
    SquareMatrix subMat = {
        .n = mat.n - 1,
        .els = subMatEls
    };

    if(mat.n == 2){
        return ((mat.els[0][0] * mat.els[1][1]) - (mat.els[0][1] * mat.els[1][0]));
    }else{
        //x is the element in the first row to ignore
        for(int x = 0; x < mat.n; x++){
            int subi = 0;
            //i is used to copy each element bar the first in each column, - iterates through rows
            for(int i = 1; i < mat.n; i++){
                int subj = 0;

                //j iterates through columns
                for(int j = 0; j < mat.n; j++){
                    if(j == x) continue;

                    subMatEls[subi][subj] = mat.els[i][j];
                    subj++;
                }

            subi++;
            }

            det += (pow(-1, x) * mat.els[0][x] * determinant(subMat));
        }
    }

    deinit_square_matrix(subMat);
    return det;
}

//B is a column vector corresponding to Ax = B
//result should be an empty column vector of size A.n, to store the results of the linsolve
void cramer_solve(SquareMatrix A, double* B, double* result){

    double det_A = determinant(A);

    for(int j = 0; j < A.n; j++){
        SquareMatrix tmp = copy_square_matrix(A);
        
        for(int i = 0; i < A.n; i++){
            tmp.els[i][j] = B[i];
        }

        double det_tmp = determinant(tmp);
        result[j] = det_tmp/det_A;
               
        deinit_square_matrix(tmp);
    }
}

