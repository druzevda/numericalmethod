#include "Matrix.h"
double** deleteMatrix(double** matrix, int rowSize) {
    for (int i = 0; i < rowSize; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return nullptr;
}
double** getMatrix(int rowSize, int colSize) {
    double** res = new double*[rowSize];
    for (int i = 0; i < rowSize; ++i) {
        res[i] = new double[colSize];
    }
    return res;
}
void fillRandomMatrix(double** ptr, int rowSize, int colSize) {
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            ptr[i][j] = random_();
        }
    }
}
