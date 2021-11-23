#include "Vector.h"

#include <functional>
#include <iostream>
extern std::function<double()> random_;
double* getVector(int size) {
    double* res = new (std::nothrow) double[size];
    if (res == nullptr) {
        std::cerr << "error no memory for vector" << std::endl;
        exit(1);
    }
    return res;
}
void fillRandomVector(double* ptr, int size) {
    for (int i = 0; i < size; ++i) {
        ptr[i] = random_();
    }
}
