#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>

#include "foo.h"
template<int rowsize, int colsize>
double getdelta(const Matrix<rowsize, colsize>& a, const Vector<colsize>& b, const Vector<colsize>& x) {
    double maxdelta = 0.0;
    for (int i = 0; i < rowsize; ++i) {
        double newdelta = b[i];
        for (int j = 0; j < colsize; ++j) {
            newdelta -= a[i][j] * x[j];
        }
        if (std::abs(newdelta) > maxdelta) {
            maxdelta = std::abs(newdelta);
        }
    }
    return maxdelta;
}
template<int rowsize, int colsize>
void fillMatrix(Matrix<rowsize, colsize>& matr) {
    matr[0][0] = 2.0;
    matr[0][1] = 0.3;
    matr[0][2] = 0.5;

    matr[1][0] = 0.1;
    matr[1][1] = 3.0;
    matr[1][2] = 0.4;

    matr[2][0] = 0.1;
    matr[2][1] = 0.1;
    matr[2][2] = 4.8;
}

template<int size>
void fillE(Matrix<size>& E) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            E[i][j] = i == j ? 1.0 : 0.0;
        }
    }
}
template<int size>
Vector<size> method(const Matrix<size, size>& A, const Vector<size>& B, const double tay, const double eps) {
    Vector<size> Xk;
    Vector<size> Xkp;
    Matrix<size, size> E;
    fillE(E);

    // xkp = (E-tay*A)*xk + tay*B;
    // xkp = M*xk + N;

    Matrix<size, size> M = E - A * tay;
    Vector<size> N       = B * tay;

    do {
        Xk  = std::move(Xkp);
        Xkp = M * Xk + N;
    } while (getdelta(A, B, Xkp) > eps);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return Xkp;
}

#define size 3
int main() {
    assert(0 && "TODO : add stop divergence criterion");
    static_assert(0 && "TODO : add stop divergence criterion");
    std::cout << std::setprecision(15);
    Matrix<size, size> A;
    Vector<size> B(1);
    fillMatrix(A);
    const double eps  = 0.000001;
    const double dtay = 0.01;
    for (double tay = eps; tay < 0.4; tay += dtay) {
        std::cout << "tay = " << tay << std::endl;
        Vector<size> x = method(A, B, tay, eps);
        x.print();
    }
}
