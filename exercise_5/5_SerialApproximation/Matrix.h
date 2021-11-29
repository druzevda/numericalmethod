#pragma once
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
extern std::function<double()> random_;

double** deleteMatrix(double** matrix, int rowSize);
double** getMatrix(int rowSize, int colSize);
void fillRandomMatrix(double** ptr, int rowSize, int colSize);

template<int rowSize, int colSize = rowSize>
class Matrix {
   public:
    double** getPtr() {
        return ptr;
    }
    Matrix() {
        ptr = getMatrix(rowSize, colSize);
        //  fillRandomMatrix(ptr, rowSize, colSize);
    }
    void fillRandom() {
        fillRandomMatrix(ptr, rowSize, colSize);
    }
    void print() const {
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                std::cout << std::setw(12) << ptr[i][j] << "        ";
            }
            std::cout << std::endl;
        }
    }
    Matrix(const Matrix<rowSize, colSize>& other) {
        ptr = getMatrix(rowSize, colSize);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                ptr[i][j] = other[i][j];
            }
        }
    }
    Matrix(Matrix<rowSize, colSize>&& other) {
        std::swap(ptr, other.ptr);
    }
    const Matrix<rowSize, colSize>& operator=(Matrix<rowSize, colSize>&& other) {
        std::swap(ptr, other.ptr);
        return *this;
    }
    const Matrix<rowSize, colSize>& operator=(const Matrix<rowSize, colSize>& other) {
        ptr = getMatrix(rowSize, colSize);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                ptr[i][j] = other[i][j];
            }
        }
    }
    Matrix<colSize, rowSize> getT() const {
        Matrix<colSize, rowSize> res;
        for (int i = 0; i < colSize; ++i) {
            for (int j = 0; j < rowSize; ++j) {
                res[i][j] = ptr[j][i];
            }
        }
        return res;
    }
    ~Matrix() {
        ptr = deleteMatrix(ptr, rowSize);
    }
    double* operator[](int pos) {
        return ptr[pos];
    }
    const double* operator[](int pos) const {
        return ptr[pos];
    }

   private:
    double** ptr{nullptr};
};
