#pragma once
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
static std::random_device rd;
static std::mt19937 random_(rd());
static std::uniform_real_distribution<> random__(-2.0, 2.0);
enum class HowToInit {
    RAND,
    IDENTITY,
    ZERO,
};
template<int SIZE>
class matrix {
   public:
    using value_type = double;
    using size_type  = int;

   private:
    double** ptr{nullptr};
    int size{SIZE};
    void _randomInit();
    void _identityInit();
    void _zeroInit();

   public:
    matrix(HowToInit how);
    ~matrix();
    matrix(const matrix<SIZE>& other);
    const matrix<SIZE>& operator=(const matrix<SIZE>& other);
    void print() const;
    double*& operator[](int pos) {
        return ptr[pos];
    }
    const double* operator[](int pos) const {
        return ptr[pos];
    }
    matrix<SIZE> operator*(const matrix<SIZE>& other);
    matrix<SIZE> getInverse();
    double det() const;
};
template<int SIZE>
void matrix<SIZE>::_randomInit() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = random__(random_);
        }
    }
}
template<int SIZE>
void matrix<SIZE>::_zeroInit() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = 0;
        }
    }
}
template<int SIZE>
void matrix<SIZE>::_identityInit() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = i == j ? 1 : 0;
        }
    }
}
template<int SIZE>
matrix<SIZE>::matrix(HowToInit how) : size(SIZE) {
    ptr = new double*[size];
    for (int i = 0; i < size; ++i) {
        ptr[i] = new double[size];
    }
    if (how == HowToInit::RAND) {
        _randomInit();
    } else if (how == HowToInit::IDENTITY) {
        _identityInit();
    } else if (how == HowToInit::ZERO) {
        _zeroInit();
    }
}
template<int SIZE>
matrix<SIZE>::~matrix() {
    for (int i = 0; i < size; ++i) {
        delete[] ptr[i];
    }
    delete[] ptr;
}
template<int SIZE>
matrix<SIZE>::matrix(const matrix<SIZE>& other) {
    size = other.size;
    ptr  = new double*[size];
    for (int i = 0; i < size; ++i) {
        ptr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = other[i][j];
        }
    }
}
template<int SIZE>
const matrix<SIZE>& matrix<SIZE>::operator=(const matrix<SIZE>& other) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ptr[i][j] = other[i][j];
        }
    }
    return *this;
}
template<int SIZE>
matrix<SIZE> matrix<SIZE>::operator*(const matrix<SIZE>& other) {
    matrix<SIZE> res(HowToInit::ZERO);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                res[i][j] += ptr[i][k] * other[k][j];
            }
        }
    }

    return res;
}
template<int SIZE>
void matrix<SIZE>::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(13) << ptr[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
template<int SIZE>
matrix<SIZE> matrix<SIZE>::getInverse() {
    matrix<SIZE> identy(HowToInit::IDENTITY);
    if (std::abs(det()) < 10e-10) {
        return identy;
    }
    matrix<SIZE> matr = *this;
    matrix<SIZE> result(HowToInit::ZERO);
    ////////////////////////////////////////
    for (int i = 0; i < size; ++i) {
        int maxLeftElemStrNumber = i;
        for (int l = i; l < size; ++l) {
            if (matr[l][i] > matr[maxLeftElemStrNumber][i]) {
                maxLeftElemStrNumber = l;
            }
        }
        std::swap(matr.ptr[maxLeftElemStrNumber], matr.ptr[i]);
        std::swap(identy.ptr[maxLeftElemStrNumber], identy.ptr[i]);
        const double leftElemMatr = matr[i][i];
        for (int j = 0; j < size; ++j) {
            matr[i][j] /= leftElemMatr;
            identy[i][j] /= leftElemMatr;
        }
        for (int k = i + 1; k < size; ++k) {
            const double mult = matr[k][i];
            for (int l = 0; l < size; ++l) {
                matr[k][l] -= matr[i][l] * mult;
                identy[k][l] -= identy[i][l] * mult;
            }
        }
    }
    for (int j = size - 1; j >= 0; --j) {
        for (int i = size - 1; i >= 0; --i) {
            double resijelem = (identy[i][j]);
            for (int k = 0; k < SIZE; ++k) {
                resijelem -= matr[i][k] * result[k][j];
            }
            result[i][j] = resijelem;
        }
    }
    /*
    for (int j = size - 1; j >= 0; --j) {
        for (int i = size - 1; i >= 0; --i) {
            double resijelem = identy[i][j];
            for (int k = 0; k < size; ++k) {
                if (k != j) resijelem -= matr[i][k] * result[k][i];
            }
            result[i][j] = resijelem / matr[i][j];

            std::cout << "++++++++++++++++=" << std::endl;
            matr.print();
            result.print();
            identy.print();
            std::cout << "++++++++++++++++=" << std::endl;
        }
    }
    */
    ////////////////////////////////////////
    /*
    for (int i = size - 1; i >= 0; --i) {
        const double rightElemMatr = matr[i][i];
        for (int j = 0; j < size; ++j) {
            matr[i][j] /= rightElemMatr;
            res[i][j] /= rightElemMatr;
        }
        for (int k = i - 1; k >= 0; --k) {
            const double mult = matr[k][i];
            for (int l = 0; l < size; ++l) {
                matr[k][l] -= matr[i][l] * mult;
                res[k][l] -= res[i][l] * mult;
            }
        }
    }
    ////////////////////////////////////////
    */

    return result;
}
template<int SIZE>
double matrix<SIZE>::det() const {
    auto clearMemory = [](double** a, int n) {
        for (int i = 0; i < n; i++) {
            delete[] a[i];
        }
        delete[] a;
    };

    std::function<double(double**, int)> findDet = [&](double** a, int n) {
        if (n == 1)
            return a[0][0];
        else if (n == 2)
            return a[0][0] * a[1][1] - a[0][1] * a[1][0];
        else {
            double d = 0;
            for (int k = 0; k < n; k++) {
                double** m = new double*[n - 1];
                for (int i = 0; i < n - 1; i++) {
                    m[i] = new double[n - 1];
                }
                for (int i = 1; i < n; i++) {
                    int t = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == k) continue;
                        m[i - 1][t] = a[i][j];
                        t++;
                    }
                }
                d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
                clearMemory(m, n - 1);  //Освобождаем память, выделенную под алгебраическое дополнение
            }
            return d;  //Возвращаем определитель матрицы
        }
    };
    return findDet(ptr, size);
}
