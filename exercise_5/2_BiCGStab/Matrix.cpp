#include "Matrix.h"
double** deleteMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return nullptr;
}
double** getMatrix(int size) {
    double** res = nullptr;
    res          = new (std::nothrow) double*[size];
    if (res == nullptr) {
        std::cerr << "error no memory for matrix" << std::endl;
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        res[i] = new (std::nothrow) double[size];
        if (res[i] == nullptr) {
            std::cerr << "error no memory for matrix" << std::endl;
            exit(1);
        }
    }
    return res;
}
void fillRandomMatrix(double** ptr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = random_();
        }
    }
}
