#pragma once
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
extern std::function<double()> random_;

double** deleteMatrix(double** matrix, int size);
double** getMatrix(int size);
void fillRandomMatrix(double** ptr, int size);

template<int SIZE>
class Matrix {
   public:
    Matrix() {
        ptr = getMatrix(size);
        fillRandomMatrix(ptr, size);
    }
    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << std::setw(12) << ptr[i][j] << "        ";
            }
            std::cout << std::endl;
        }
    }
    Matrix(const Matrix<SIZE>& other) {
        ptr = getMatrix(SIZE);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                ptr[i][j] = other[i][j];
            }
        }
    }
    Matrix(Matrix<SIZE>&& other) {
        std::swap(ptr, other.ptr);
    }
    const Matrix<SIZE>& operator=(Matrix<SIZE>&& other) {
        std::swap(ptr, other.ptr);
        return *this;
    }
    const Matrix<SIZE>& operator=(const Matrix<SIZE>& other) {
        ptr = getMatrix(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                ptr[i][j] = other[i][j];
            }
        }
    }
    ~Matrix() {
        ptr = deleteMatrix(ptr, SIZE);
    }
    double* operator[](int pos) {
        return ptr[pos];
    }
    const double* operator[](int pos) const {
        return ptr[pos];
    }

   private:
    double** ptr{nullptr};
    int size{SIZE};
};
