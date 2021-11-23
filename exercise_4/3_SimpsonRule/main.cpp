#include <cmath>
#include <iostream>
double f(double x) {
    return exp(sin(x));
}
double simpsonRule(const double a, const double b, const int n) {
    const double delta = (b - a) / n;
    double res         = f(a) + f(b);
    for (int i = 1; i <= n - 1; ++i) {
        if (i % 2 == 0)
            res += 4 * f(a + i * delta);
        else
            res += 2 * f(a + i * delta);
    }
    return res * delta / 3;
}
int main() {
    const double a   = 0.0;
    const double b   = 1.0;
    const int n      = 90;
    const double res = simpsonRule(a, b, n);
    std::cout << res << std::endl;
}
