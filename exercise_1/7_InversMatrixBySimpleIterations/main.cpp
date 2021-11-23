#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

void print(double** a, int size) {
    std::cout << "------------------" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(10) << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "------------------" << std::endl;
}
double** getMemoryMatrix(int size) {
    double** a = new double*[size];
    for (int i = 0; i < size; ++i) {
        a[i] = new double[size];
    }
    return a;
}
double** deleteMemoryMatrix(double** a, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] a[i];
    }
    delete[] a;
    return nullptr;
}
void setRandom(double** a, int size) {
    std::mt19937 rd_(std::random_device{}());
    std::uniform_real_distribution<> genrand(-5.0, 5.0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = genrand(rd_);
        }
    }
}
void copyMatrix(double** from, double** to, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            to[i][j] = from[i][j];
        }
    }
}
double getDeterminant(double** A, int size) {
    double** a = getMemoryMatrix(size);
    copyMatrix(A, a, size);
    double mult = 1.0;
    for (int i = 0; i < size; ++i) {
        int maxstrcount = i;
        /////////////////////////////////////////
        // choice diagonal element
        // max in column
        for (int j = i + 1; j < size; ++j) {
            if (a[maxstrcount][i] < a[j][i]) {
                maxstrcount = j;
            }
        }
        if (i != maxstrcount) {
            // change among ourselves str
            std::swap(a[i], a[maxstrcount]);
            mult *= -1;
        }
        /////////////////////////////////////////
        // set zero under diagonal
        for (int j = i + 1; j < size; ++j) {
            const double mult = a[j][i] / a[i][i];
            for (int k = 0; k < size; ++k) {
                a[j][k] -= mult * a[i][k];
            }
        }
        /////////////////////////////////////////
    }
    /////////////////////////////////////////
    double det = 1;
    // multiply elements at diagonal
    for (int i = 0; i < size; ++i) {
        det *= a[i][i];
    }
    a = deleteMemoryMatrix(a, size);
    return det * mult;
    /////////////////////////////////////////
}

void testValues(double** A) {
    A[0][0] = 4;
    A[0][1] = -1;
    A[0][2] = 1;
    A[1][0] = 2;
    A[1][1] = 6;
    A[1][2] = -1;
    A[2][0] = 1;
    A[2][1] = 2;
    A[2][2] = -3;
}
double test(double** A, double** B, int size) {
    double delta = 0.0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::abs(A[i][j] - B[i][j]) > delta) {
                delta = std::abs(A[i][j] - B[i][j]);
            }
        }
    }
    return delta;
}
int main() {
    std::cout << std::setprecision(6);
    const int size = 3;
    double** a     = getMemoryMatrix(size);

    setRandom(a, size);
    // testValues(a, b);

    print(a, size);

    a = deleteMemoryMatrix(a, size);
}
