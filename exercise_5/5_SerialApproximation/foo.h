#include "Matrix.h"
#include "Vector.h"
template<int SIZE>
Vector<SIZE> operator-(const Vector<SIZE>& A, const Vector<SIZE>& B) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = A[i] - B[i];
    }
    return res;
}
template<int SIZE>
Vector<SIZE> operator+(const Vector<SIZE>& A, const Vector<SIZE>& B) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = A[i] + B[i];
    }
    return res;
}
template<int SIZE>
double operator*(const Vector<SIZE>& A, const Vector<SIZE>& B) {
    double res = 0;
    for (int i = 0; i < SIZE; ++i) {
        res += A[i] * B[i];
    }
    return res;
}

template<int rowSize, int colSize>
Vector<rowSize> operator*(const Matrix<rowSize, colSize>& A, const Vector<colSize>& B) {
    Vector<rowSize> res;
    for (int i = 0; i < rowSize; ++i) {
        res[i] = 0;
        for (int j = 0; j < colSize; ++j) {
            res[i] += (A[i][j]) * B[j];
        }
    }
    return res;
}

template<int rowSize, int colSize>
Matrix<rowSize, colSize> operator-(const Matrix<rowSize, colSize>& A, const Matrix<rowSize, colSize>& B) {
    Matrix<rowSize, colSize> res;
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
    return res;
}
template<int rowSize, int center, int colSize>
Matrix<rowSize, colSize> operator*(const Matrix<rowSize, center>& A, const Matrix<center, colSize>& B) {
    Matrix<rowSize, colSize> res;
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < center; ++k) {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return res;
}
template<int SIZE>
Vector<SIZE> operator*(const Vector<SIZE>& A, double n) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = A[i] * n;
    }
    return res;
}
template<int SIZE>
Vector<SIZE> operator*(double n, const Vector<SIZE>& A) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = A[i] * n;
    }
    return res;
}
template<int rowSize, int colSize>
Matrix<rowSize, colSize> operator*(const Matrix<rowSize, colSize>& other, const double n) {
    Matrix<rowSize, colSize> ptr;
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            ptr[i][j] = other[i][j] * n;
        }
    }
    return ptr;
}
