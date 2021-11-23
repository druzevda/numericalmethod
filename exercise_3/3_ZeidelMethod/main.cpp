#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

using func = std::function<double(const std::vector<double>&)>;

void printVec(const std::vector<double>& vec) {
    for (auto& x : vec) {
        std::cout << std::setw(20) << x << ' ';
    }
    std::cout << std::endl;
}
double calcMaxDelta(const std::vector<func>& func, const std::vector<double>& x) {
    double delta = 0.0;
    for (auto& f : func) {
        const double newDelta = f(x);
        if (std::abs(newDelta) > delta) {
            delta = std::abs(newDelta);
        }
    }
    return delta;
}
void zeidelAlg(const std::vector<func>& f, const std::vector<func>& phi, std::vector<double>& x, const double eps) {
    while (std::abs(calcMaxDelta(f, x)) > eps) {
        for (std::size_t i = 0; i < f.size(); ++i) {
            x[i] = phi[i](x);
        }
        printVec(x);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    std::cout << std::setprecision(15);
    const double eps = 1e-15;

    auto f1 = [](const std::vector<double>& x) {
        return sin(x[0] + x[1]) - 1.2 * x[0] - 0.2;
    };
    auto f2 = [](const std::vector<double>& x) {
        return x[0] * x[0] + x[1] * x[1] - 1;
    };

    auto phi1 = [f1](const std::vector<double>& x) {
        return x[0] + f1(x);
    };
    auto phi2 = [f2](const std::vector<double>& x) {
        return x[1] + f2(x);
    };

    std::vector<func> f{f1, f2};
    std::vector<func> phi{phi1, phi2};

    std::vector<double> x{0, 0};
    zeidelAlg(f, phi, x, eps);
    const double maxDelta = calcMaxDelta(f, x);
    std::cout << "----------------------" << std::endl;
    printVec(x);
    std::cout << "----------------------" << std::endl;
    std::cout << "maxdelta = " << maxDelta << std::endl;
}
