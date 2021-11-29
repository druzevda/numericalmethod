#include <cmath>
#include <iomanip>
#include <iostream>
double func(double x) {
    return cos(x * x * x) * exp(-x * x);
}
template<typename foo>
double newthonMethod(const double a, const double b, const int n, foo f) {
    if (n % 3 != 0) {
        std::cerr << "error n%3 != 0" << std::endl;
        exit(1);
    }
    const double delta = (b - a) / n;
    double res         = f(a) + f(b);
    for (int i = 1; i < n; ++i) {
        if (i % 3 == 0)
            res += 2 * f(a + i * delta);
        else
            res += 3 * f(a + i * delta);
    }
    return 3 * delta / 8 * res;
}
template<typename foo>
double integralWithEps(const double a, const double b, const double eps, foo f) {
    double Ik  = 0.0;
    double Ikp = 0.0;
    int n      = 3;
    do {
        Ik  = Ikp;
        Ikp = newthonMethod(a, b, n, f);
        // std::cout << "\t\tI = " << Ikp << " n = " << n << std::endl;
        n *= 2;
    } while (std::abs(Ik - Ikp) > eps);
    std::cout << "\t\tn = " << n << std::endl;
    return Ikp;
}
int main() {
    std::cout << std::setprecision(10);
    double a         = 0.0;
    double b         = 1.0;
    const double eps = 1e-8;
    double resk      = 0.0;
    double reskp     = 0.0;
    do {
        std::cout << "a = " << a << " b =  " << b << std::endl;

        resk  = reskp;
        reskp = integralWithEps(a, b, eps, func);
        b += 1.0;
        std::cout << "\t\tint = " << std::setw(10) << reskp << std::endl;
    } while (std::abs(resk - reskp) > eps);
}
