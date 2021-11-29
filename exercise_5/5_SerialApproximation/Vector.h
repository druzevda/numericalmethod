#pragma once
#include <iomanip>
#include <iostream>
void fillRandomVector(double*, int);
double* getVector(int);

template<int SIZE>
class Vector {
   public:
    double* getPtr() {
        return ptr;
    }
    explicit Vector(int value) {
        ptr = new double[SIZE];
        for (int i = 0; i < size; ++i) {
            ptr[i] = value;
        }
    }
    Vector() {
        ptr = new double[SIZE];
        //        fillRandomVector(ptr, size);
    }
    void fillRandom() {
        fillRandomVector(ptr, size);
    }
    void print() const {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(12) << ptr[j] << " ";
        }
        std::cout << std::endl;
    }
    Vector(const Vector<SIZE>& other) {
        ptr = getVector(SIZE);
        for (int i = 0; i < size; ++i) {
            ptr[i] = other[i];
        }
    }
    Vector(Vector<SIZE>&& other) {
        std::swap(ptr, other.ptr);
    }

    ~Vector() {
        delete[] ptr;
    }
    const Vector<SIZE>& operator=(const Vector<SIZE>& other) {
        for (int i = 0; i < size; ++i) {
            ptr[i] = other[i];
        }
        return *this;
    }
    const Vector<SIZE>& operator=(Vector<SIZE>&& other) {
        std::swap(ptr, other.ptr);
        return *this;
    }

    double& operator[](int pos) {
        return ptr[pos];
    }
    double operator[](int pos) const {
        return ptr[pos];
    }

   private:
    double* ptr{nullptr};
    int size{SIZE};
};

