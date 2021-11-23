#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

void print(double** a, double* b, int size) {
    std::cout << "------------------" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(10) << a[i][j] << ' ';
        }
        std::cout << '\t' << '\t' << b[i] << '\n';
    }
    std::cout << "------------------" << std::endl;
}
double* getMemoryStr(int size) {
    return new double[size];
}
double* deleteMemoryStr(double* a) {
    delete[] a;
    return nullptr;
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
void setRandom(double** a, double* b, int size) {
    std::mt19937 rd_(std::random_device{}());
    std::uniform_real_distribution<> genrand(-5.0, 5.0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = genrand(rd_);
        }
        b[i] = genrand(rd_);
    }
}
void copyMatrix(double** from, double** to, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            to[i][j] = from[i][j];
        }
    }
}
void copyStr(double* from, double* to, int size) {
    for (int i = 0; i < size; ++i) {
        to[i] = from[i];
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
void printStr(double* X, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(7) << X[i] << std::endl;
    }
    std::cout << std::endl;
}
void jordanGaussMethod(double** A, double* B, double* X, int size) {
    if (std::abs(getDeterminant(A, size)) < 1e-10) {
        std::cout << "det ~=0" << std::endl;
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        int maxstrcount = i;
        /////////////////////////////////////////
        // choice diagonal element
        // max in column
        for (int j = i + 1; j < size; ++j) {
            if (A[maxstrcount][i] < A[j][i]) {
                maxstrcount = j;
            }
        }
        std::swap(A[i], A[maxstrcount]);
        std::swap(B[i], B[maxstrcount]);
        const double diagElem = A[i][i];
        for (int j = 0; j < size; ++j) {
            A[i][j] /= diagElem;
        }
        B[i] /= diagElem;
        /////////////////////////////////////////
        // set zero under diagonal
        for (int j = i + 1; j < size; ++j) {
            const double mult = A[j][i] / A[i][i];
            for (int k = 0; k < size; ++k) {
                A[j][k] -= mult * A[i][k];
            }
            B[j] -= mult * B[i];
        }
    }
    for (int j = size - 1; j >= 0; --j) {
        for (int i = j - 1; i >= 0; --i) {
            const double mult = A[i][j] / A[j][j];
            A[i][j] -= A[j][j] * mult;
            B[i] -= B[j] * mult;
        }
    }
    copyStr(B, X, size);
}
void testValues(double** A, double* B) {
    A[0][0] = 4;
    A[0][1] = -1;
    A[0][2] = 1;
    A[1][0] = 2;
    A[1][1] = 6;
    A[1][2] = -1;
    A[2][0] = 1;
    A[2][1] = 2;
    A[2][2] = -3;
    B[0]    = 4;
    B[1]    = 7;
    B[2]    = 0;
}
double test(double** A, double* B, double* X, int size) {
    double delta = 0.0;
    for (int i = 0; i < size; ++i) {
        double res = 0.0;
        for (int j = 0; j < size; ++j) {
            res += A[i][j] * X[j];
        }
        if (std::abs(res - B[i]) > delta) {
            delta = std::abs(res - B[i]);
        }
    }
    return delta;
}
int main() {
    std::cout << std::setprecision(6);
    const int size = 3;
    double** a     = getMemoryMatrix(size);
    double* b      = getMemoryStr(size);
    double* x      = getMemoryStr(size);

    setRandom(a, b, size);
    // testValues(a, b);

    print(a, b, size);
    jordanGaussMethod(a, b, x, size);
    print(a, b, size);
    printStr(x, size);

    std::cout << test(a, b, x, size) << std::endl;
    a = deleteMemoryMatrix(a, size);
    b = deleteMemoryStr(b);
    x = deleteMemoryStr(x);
}
