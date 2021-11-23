#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <thread>
double f(const double x) {
    return sin(x * x) - 6 * x + 1;
}
double f(const double x_1, const double x_0) {
    return (f(x_0) - f(x_1)) / (x_0 - x_1);
}
double f(const double x_2, const double x_1, const double x_0) {
    return (f(x_1, x_0) - f(x_2, x_1)) / (x_0 - x_2);
}
double searchRoot(const double x_0, const double x_2, const double eps) {
    const double x_1 = (x_0 + x_2) / 2;
    // P(x) = f(x_0) + f(x_0,x_1)(x-x_0) + f(x_0,x_1,x_2)(x-x_0)(x-x_2);
    //
    // P(x) = f(x_0) + [f(x_0,x_1) + f(x_0,x_1,x_2)*(x_0-x_1)](x-x_0) + f(x_0,x_1,x_2)*(x-a)^2;

    const double c = f(x_0);
    const double b = f(x_0, x_1) + f(x_0, x_1, x_2) * (x_0 - x_1);
    const double a = f(x_0, x_1, x_2);

    const double root1 = x_0 - (2 * c) / (b + std::sqrt(b * b - 4 * a * c));
    const double root2 = x_0 - (2 * c) / (b - std::sqrt(b * b - 4 * a * c));
    double x;
    if ((x_0 <= root1 && x_2 >= root1) || (x_0 >= root1 && x_2 <= root1)) {
        x = root1;
    } else {
        x = root2;
    }
    std::cout << x << std::endl;
    //    if (std::abs(x_0 - x) < eps) return x;
    if (std::abs(f(x)) < eps) return x;
    return f(a) * f(x) < 0 ? searchRoot(a, x, eps) : searchRoot(x, b, eps);
}
int main() {
    std::cout << std::setprecision(9);
    constexpr double eps = 1e-10;
    constexpr double a   = -100.0;
    constexpr double b   = 100.0;

    double x = searchRoot(a, b, eps);
    double y = f(x);

    std::cout << "-----------------------" << std::endl;
    std::cout << std::setprecision(9) << x << std::endl;
    std::cout << std::setprecision(9) << y << std::endl;
}
