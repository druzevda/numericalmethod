#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <thread>
double f(const double x) {
    return sin(x * x) - 6 * x + 1;
}
double searchRoot(const double a, const double b, const double eps = 1e-5) {
    const double c = (a + b) / 2;
    if (std::abs(f(c)) < eps) return c;
    std::cout << c << std::endl;
    if (f(a) * f(c) < 0)
        return searchRoot(a, c, eps);
    else
        return searchRoot(c, b, eps);
}
int main() {
    constexpr double eps = 1e-10;
    constexpr double a   = -100;
    constexpr double b   = 100;
    const double x       = searchRoot(a, b, eps);
    const double y       = f(x);

    std::cout << "-----------------------" << std::endl;
    std::cout << std::setprecision(9) << x << std::endl;
    std::cout << std::setprecision(9) << y << std::endl;
}
