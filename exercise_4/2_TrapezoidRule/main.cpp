#include <cmath>
#include <iostream>
double f(double x) {
    return x * sin(x);
}
double trapezoidRule(const double a, const double b, const int n) {
    const double delta = (b - a) / n;
    double res         = 0.0;
    res                = (f(a) + f(b)) / 2;
    for (int i = 1; i < n; ++i) {
        res += f(a + i * delta);
    }
    return res * delta;
}
int main() {
    const double a   = 0.0;
    const double b   = 1.0;
    const int n      = 1000;
    const double res = trapezoidRule(a, b, n);
    std::cout << res << std::endl;
}
