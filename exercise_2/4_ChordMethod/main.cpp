#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <thread>
double f(const double x) {
    return -x * x + sin(x);
}
double searchRoot(const double a, const double b, const double eps = 1e-5) {
    if (std::abs(f(a)) < eps) return a;
    if (std::abs(f(b)) < eps) return b;

    const double c = a - (b - a) / (f(b) - f(a)) * f(a);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << a << ' ' << c << ' ' << b << std::endl;

    return (f(a) * f(c) < 0) ? searchRoot(a, c, eps) : searchRoot(c, b, eps);
}
int main() {
    constexpr double eps = 1e-10;

    constexpr double a = 1.0;
    constexpr double b = 5.0;

    const double x = searchRoot(a, b, eps);
    const double y = f(x);

    std::cout << "-----------------------" << std::endl;
    std::cout << std::setprecision(9) << x << std::endl;
    std::cout << std::setprecision(9) << y << std::endl;
}
