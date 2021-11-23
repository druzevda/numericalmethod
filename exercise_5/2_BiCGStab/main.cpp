#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "foo.h"
std::mt19937 mersene(std::random_device{}());
std::uniform_real_distribution<> normal(-10.0, 10.0);

std::function<double()> random_ = []() {
    return normal(mersene);
};
void fill(Matrix<4>& A, Vector<4>& B) {
    A[0][0] = 1;
    A[0][1] = 5;
    A[0][2] = 7;
    A[0][3] = 8;
    A[1][0] = 3;
    A[1][1] = 1;
    A[1][2] = 2;
    A[1][3] = 9;
    A[2][0] = 4;
    A[2][1] = 2;
    A[2][2] = 2;
    A[2][3] = 7;
    A[3][0] = 5;
    A[3][1] = 9;
    A[3][2] = 9;
    A[3][3] = 1;
    B[0]    = 7;
    B[1]    = 4;
    B[2]    = 1;
    B[3]    = 8;
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
    std::cout << "x_0 = ";
    x_k.print();
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
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "x_" << i++ << " = ";
        x_kp.print();
    }
    return x_kp;
}
template<int SIZE>
double getDelta(const Matrix<SIZE>& A, const Vector<SIZE>& B, const Vector<SIZE>& X) {
    double maxDelta = 0.0;
    for (int i = 0; i < SIZE; ++i) {
        double newDelta = B[i];
        for (int j = 0; j < SIZE; ++j) {
            newDelta -= A[i][j] * X[j];
        }
        if (std::abs(newDelta) > maxDelta) {
            maxDelta = std::abs(newDelta);
        }
    }
    return maxDelta;
}
int main() {
    std::cout << std::setprecision(5);
    Matrix<4> A;
    const double eps = 1e-11;
    Vector<4> B;
    fill(A, B);
    Vector<4> X = BiCGStab(A, B, eps);
    std::cout << "--------A------------------" << std::endl;
    A.print();
    std::cout << "--------B------------------" << std::endl;
    B.print();
    std::cout << "--------X------------------" << std::endl;
    X.print();
    std::cout << "---------------------------" << std::endl;
    std::cout << "maxDelta = " << getDelta(A, B, X) << std::endl;
}
