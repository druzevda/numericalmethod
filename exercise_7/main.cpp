#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>

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
void fill(Vector<SIZE>& X, const double a, const double b, const int N) {
    const double delta = (b - a) / N;
    for (int i = 0; i < SIZE; ++i) {
        X[i] = a + i * delta;
    }
}
double rectangleCf(int i, double delta, int N) {
    i = N;
    N = i;
    return delta;
}
double trapezoidCf(int i, double delta, int N) {
    if (i == 0 || i == N)
        return delta / 2.0;
    else
        return delta;
}
double simpsonCf(int i, double delta, int N) {
    double cf = 0.0;
    if (i == 0 || i == N)
        cf = 1.0;
    else if (i % 2 == 0)
        cf = 4.0;
    else
        cf = 2.0;
    return cf * delta / 3;
}
template<int SIZE>
Vector<SIZE> BiCGStab(const Matrix<SIZE>& A, const Vector<SIZE>& B, const double eps) {
    Vector<SIZE> x_k;
    Vector<SIZE> x_kp;

    Vector<SIZE> r_tilda;
    Vector<SIZE> r_k;  // невязка
    Vector<SIZE> r_kp;

    Vector<SIZE> p_k;  // базисный вектор подпространства крылова
    Vector<SIZE> p_kp;

    Vector<SIZE> v_k;
    Vector<SIZE> v_kp;

    Vector<SIZE> s_kp;
    Vector<SIZE> t_kp;

    double rho_k;
    double rho_kp;

    double alpha_k;
    double alpha_kp;

    double omega_k;
    double omega_kp;

    x_k = Vector<SIZE>{0};
    r_k = r_tilda = B - A * x_k;

    rho_k = alpha_k = omega_k = omega_kp = 1.0;
    v_k = p_k = Vector<SIZE>{0};
    int i     = 1;
    while (getDelta(A, B, x_kp) > eps) {
        rho_kp          = r_tilda * r_k;
        double betta_kp = (rho_kp * alpha_k) / (rho_k * omega_k);
        p_kp            = r_k + betta_kp * (p_k - omega_k * v_k);  // базисный вектор подпространства крылова
        v_kp            = A * p_kp;
        alpha_kp        = rho_kp / (r_tilda * v_kp);
        s_kp            = r_k - alpha_kp * v_kp;
        t_kp            = A * s_kp;
        omega_kp        = (t_kp * s_kp) / (t_kp * t_kp);
        x_kp            = x_k + omega_kp * s_kp + alpha_kp * p_kp;
        r_kp            = s_kp - omega_kp * t_kp;

        rho_k   = rho_kp;
        p_k     = p_kp;
        alpha_k = alpha_kp;
        x_k     = x_kp;
        v_k     = v_kp;
        r_k     = r_kp;
        omega_k = omega_kp;
        ++i;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << i << "  iterations" << std::endl;
    return x_kp;
}
template<int SIZE, typename callable>
double calcMaxDelta(const Vector<SIZE>& X, const Vector<SIZE>& Y, callable Answer) {
    double maxDelta = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        double nowDelta = std::abs(Y[i] - Answer(X[i]));
        if (nowDelta > maxDelta) {
            maxDelta = nowDelta;
        }
    }
    return maxDelta;
}

int main() {
    std::cout << std::setprecision(10);

    constexpr int size        = 100;
    constexpr int nodesAmount = size + 1;

    constexpr double a     = 0.0;
    constexpr double b     = 1.0;
    constexpr double eps   = 0.000001;
    constexpr double delta = (b - a) / size;

    auto Answer = [](double x) {
        return exp(x) * (1 + 2 * x);
        // return 0;
    };
    auto Cf = [size, delta](int i) {
        // return rectangleCf(i, delta, size);
        return trapezoidCf(i, delta, size);
        // return simpsonCf(i, delta, size);
    };
    auto K = [](double x, double s) {
        // return x * exp(x - s);
        return 1.0 / (1 + std::pow(cos(0.3 * (x - s)), 2));
    };
    auto F = [](double x) {
        return exp(-x);
        // return x * x + 1;
    };

    Vector<nodesAmount> X;
    Vector<nodesAmount> Y;
    Matrix<nodesAmount> A;
    Vector<nodesAmount> B;

    fill(X, a, b, size);

    for (int i = 0; i < nodesAmount; ++i) {
        A[i][i] = 1.0;
        B[i]    = F(X[i]);
        for (int j = 0; j < nodesAmount; ++j) {
            A[i][j] -= Cf(j) * K(X[i], X[j]);
        }
    }
    Y = BiCGStab(A, B, eps);
    std::cout << calcMaxDelta(X, Y, Answer) << std::endl;
    std::ofstream file("file.txt");
    for (int i = 0; i < nodesAmount; ++i) {
        file << X[i] << '\t' << Y[i] << '\t' << Answer(X[i]) << std::endl;
    }
}
