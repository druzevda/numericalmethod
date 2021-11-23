#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
const double pi = acos(-1);
const int N     = 30;
const int M     = 6;
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
double calcAk(const int k, foo f) {
    auto a = [&f, k](double x) {
        return f(x) * cos(k * x);
    };
    return 1.0 / pi * newthonMethod(-pi, pi, N, a);
}
template<typename foo>
double calcBk(const int k, foo f) {
    auto a = [&f, k](double x) {
        return f(x) * sin(k * x);
    };
    return 1.0 / pi * newthonMethod(-pi, pi, N, a);
}
int main() {
    auto f = [](double x) {
        return exp(sin(x));
    };
    const double a     = 0.0;
    const double b     = pi;
    const double delta = (b - a) / N;

    std::vector<double> ak(M, 0.0);
    std::vector<double> bk(M, 0.0);

    for (std::size_t i = 0; i < ak.size(); ++i) {
        ak[i] = calcAk(i, f);
        bk[i] = calcBk(i, f);
        std::cout << "a_" << i << " = " << ak[i] << std::endl;
        std::cout << "b_" << i << " = " << bk[i] << std::endl;
    }
    std::ofstream file("function.dat");

    for (double x = a; x < b; x += delta) {
        double res = ak[0] / 2.0;
        for (int i = 1; i < M; ++i) {
            res += ak[i] * cos(i * x) + bk[i] * sin(i * x);
        }
        file << x << '\t' << res << std::endl;
    }
}
