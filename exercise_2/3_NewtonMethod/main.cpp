#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <thread>
double f(const double x) {
    return -x * x + sin(x);
}
double f_der(const double x) {
    return -2 * x + cos(x);
}
double searchRoot(const double xk, const double eps = 1e-5) {
    if (std::abs(f(xk)) < eps) return xk;

    const double xkp1 = xk - f(xk) / f_der(xk);
    std::cout << xkp1 << std::endl;
    return searchRoot(xkp1, eps);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
int main() {
    constexpr double eps = 1e-10;
    constexpr double x_0 = 0.5;

    const double x = searchRoot(x_0, eps);
    const double y = f(x);

    std::cout << "-----------------------" << std::endl;
    std::cout << std::setprecision(9) << x << std::endl;
    std::cout << std::setprecision(9) << y << std::endl;
}
