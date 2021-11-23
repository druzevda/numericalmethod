#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#define printme(x) std::cout << #x << "          = \t" << x << std::endl;
#include "foo.h"
std::mt19937 mersene(std::random_device{}());
std::uniform_real_distribution<> normal(-10.0, 10.0);

std::function<double()> random_ = []() {
    return normal(mersene);
};
template<int rowSize, int colSize>
double getDelta(const Matrix<rowSize, colSize>& A, const Vector<colSize>& B, const Vector<colSize>& X) {
    double maxDelta = 0.0;
    for (int i = 0; i < rowSize; ++i) {
        double newDelta = B[i];
        for (int j = 0; j < colSize; ++j) {
            newDelta -= A[i][j] * X[j];
        }
        if (std::abs(newDelta) > maxDelta) {
            maxDelta = std::abs(newDelta);
        }
    }
    return maxDelta;
}
template<int SIZE>
void fillFromFile(Vector<SIZE>& X, Vector<SIZE>& Y) {
    std::ifstream file("file.txt");
    for (int i = 0; i < SIZE; ++i) {
        file >> X[i] >> Y[i];
    }
}
template<int SIZE, int M>
Matrix<SIZE, M> getF(const Vector<SIZE>& X) {
    Matrix<SIZE, M> res;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < M; ++j) {
            res[i][j] = std::pow(X[i], j);
        }
    }
    return res;
}

template<int SIZE>
Vector<SIZE> gaussMethod(Matrix<SIZE, SIZE> A, Vector<SIZE> B) {
    for (int i = 0; i < SIZE; ++i) {
        const double diagElem = A[i][i];
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] /= diagElem;
        }
        B[i] /= diagElem;
        for (int j = i + 1; j < SIZE; ++j) {
            const double mult = A[j][i] / A[i][i];
            for (int k = 0; k < SIZE; ++k) {
                A[j][k] -= mult * A[i][k];
            }
            B[j] -= mult * B[i];
        }
    }
    for (int j = SIZE - 1; j >= 0; --j) {
        for (int i = j - 1; i >= 0; --i) {
            const double mult = A[i][j] / A[j][j];
            A[i][j] -= A[j][j] * mult;
            B[i] -= B[j] * mult;
        }
    }
    return B;
}

template<int SIZE, int N>
Vector<SIZE> getP(const Vector<SIZE>& X, const Vector<N>& cf) {
    Vector<SIZE> res{0};
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < N; ++j) {
            res[i] += cf[j] * std::pow(X[i], j);
        }
    }
    return res;
}
template<int SIZE>
Vector<SIZE> getDelta(const Vector<SIZE>& Y, const Vector<SIZE>& Y_pd) {
    Vector<SIZE> res;
    for (int i = 0; i < SIZE; ++i) {
        res[i] = std::pow(Y[i] - Y_pd[i], 2);
    }
    return res;
}
template<int SIZE>
double getMaxDelta(const Vector<SIZE>& Y, const Vector<SIZE>& Y_pd) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        double newdelta = std::pow(Y[i] - Y_pd[i], 2);
        if (newdelta > res) {
            res = newdelta;
        }
    }
    return res;
}
template<int SIZE>
double getSumDelta(const Vector<SIZE>& Y, const Vector<SIZE>& Y_pd) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += std::pow(Y[i] - Y_pd[i], 2);
    }
    return res;
}
template<int SIZE>
double getAver(const Vector<SIZE>& a) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += a[i];
    }
    return res / SIZE;
}
template<int SIZE>
double d_x_1_2(const Vector<SIZE>& x, double x_i_2_aver) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += std::pow(x[i], 4);
    }
    return res / SIZE - x_i_2_aver * x_i_2_aver;
}
template<int SIZE>
double getFactDisp(const Vector<SIZE>& y, const double y_aver) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += std::pow(y_aver - y[i], 2);
    }
    return res;
}
template<int SIZE>
double chi2(const Vector<SIZE>& y, const Vector<SIZE>& y_res) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += std::pow(y[i] - y_res[i], 2);
    }
    return res;
}
template<int SIZE, int M>
double getS_y_2(const Vector<SIZE>& y, const Vector<SIZE>& y_res) {
    double chi2_ = chi2(y, y_res);
    return chi2_ / (SIZE - M);
}
template<int SIZE>
double getMagic(const Vector<SIZE>& x, const double x_aver) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += (x[i] - x_aver) * (x[i] * x[i] - x_aver * x_aver);
    }
    return res;
}
template<int SIZE>
double Sr(const Vector<SIZE>& vec) {
    double res = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        res += vec[i];
    }
    return res / SIZE;
}
template<int SIZE>
double R2(const Vector<SIZE>& y, const double Chi2) {
    double aver        = Sr(y);
    double denomenator = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        denomenator += std::pow((y[i] - aver), 2);
    }
    return 1.0 - Chi2 / denomenator;
}
#define sz 8
#define m 2
int main() {
    std::cout << std::setprecision(15);

    Vector<sz> X;
    Vector<sz> Y;
    fillFromFile(X, Y);
    X.print();
    Y.print();

    Matrix<sz, m> F  = getF<sz, m>(X);
    Matrix<m, sz> FT = F.getT();

    Matrix<m, m> A   = FT * F;
    Vector<m> B      = FT * Y;
    Vector<m> cf     = gaussMethod(A, B);
    Vector<sz> Y_res = getP(X, cf);
    std::ofstream file("data.dat");
    for (int i = 0; i < sz; ++i) {
        file << X[i] << '\t' << Y[i] << '\t' << Y_res[i] << '\t' << std::abs(Y_res[i] - Y[i]) << std::endl;
    }
    const double chi = chi2(Y, Y_res);
    const double r2  = R2(Y, chi);
    std::cout << "chi = " << chi << std::endl;
    std::cout << "r2 = " << r2 << std::endl;
    cf.print();
}
