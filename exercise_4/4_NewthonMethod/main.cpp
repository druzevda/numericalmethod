#include <cmath>
#include <iomanip>
#include <iostream>
double func(double x) {
    return (exp(x * x) + exp(-x * x)) / 2;
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
double simple(double x) {
    return x * x;
}
int main() {
    std::cout << std::setprecision(10);
    const double a   = 0.0;
    const double b   = 1.0;
    const double eps = 1e-15;
    int n            = 3;
    double res_k     = newthonMethod(a, b, n, func);
    double res_km1   = res_k + 1;
    while (std::abs(res_km1 - res_k) > eps) {
        res_km1 = res_k;
        n *= 2;
        res_k = newthonMethod(a, b, n, func);
        std::cout << std::setw(15) << n << ' ' << res_k << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    std::cout << newthonMethod(a, b, n, simple) << std::endl;
}
