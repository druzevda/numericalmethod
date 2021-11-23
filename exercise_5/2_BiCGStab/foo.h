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

template<int SIZE>
Vector<SIZE> operator*(const Matrix<SIZE>& A, const Vector<SIZE>& B) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = 0;
        for (int j = 0; j < SIZE; ++j) {
            res[i] += (A[i][j]) * B[j];
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
