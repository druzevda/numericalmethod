#pragma once
#include "matrix.h"
template<int S>
double calcMaxDiff(const matrix<S>& a, const matrix<S>& b);
void test1();
void test2();
template<int S>
double calcMaxDiff(const matrix<S>& a, const matrix<S>& b) {
    double maxDiff = 0.0;
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            const double nowDiff = std::abs(a[i][j] - b[i][j]);
            if (nowDiff > maxDiff) {
                maxDiff = nowDiff;
            }
        }
    }
    return maxDiff;
}
void test1() {
    matrix<3> a(HowToInit::RAND);
    matrix<3> b = a.getInverse();
    matrix<3> c = a * b;
    matrix<3> d(HowToInit::IDENTITY);
    std::cout << "-----------------------------------------------" << std::endl;
    a.print();
    b.print();
    c.print();
    d.print();
    std::cout << "max diff == " << (calcMaxDiff(c, d)) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}
void test2() {
    matrix<3> a(HowToInit::ZERO);
    a[0][0]     = 1.54;
    a[0][1]     = 1.70;
    a[0][2]     = 1.62;
    a[1][0]     = 3.69;
    a[1][1]     = 3.73;
    a[1][2]     = 3.59;
    a[2][0]     = 2.45;
    a[2][1]     = 2.43;
    a[2][2]     = 2.25;
    matrix<3> b = a.getInverse();
    matrix<3> c = a * b;
    matrix<3> d(HowToInit::IDENTITY);
    std::cout << "-----------------------------------------------" << std::endl;
    a.print();
    b.print();
    c.print();
    d.print();
    std::cout << "max diff == " << (calcMaxDiff(c, d)) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}
