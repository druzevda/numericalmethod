#include <functional>
#include <iomanip>
#include <iostream>
#include <random>

void print(double** a, int size) {
    std::cout << "------------------" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(10) << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "------------------" << std::endl;
}
double** getmemory(int size) {
    double** a = new double*[size];
    for (int i = 0; i < size; ++i) {
        a[i] = new double[size];
    }
    return a;
}
double** deletememory(double** a, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] a[i];
    }
    delete[] a;
    return nullptr;
}
void setrandom(double** a, int size) {
    std::mt19937 rd_(std::random_device{}());
    std::uniform_real_distribution<> genrand(0.0, 1.0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = genrand(rd_);
        }
    }
}
double getDeterminant(double** a, int size) {
    double mult = 1.0;
    for (int i = 0; i < size; ++i) {
        int maxstrcount = i;
        /////////////////////////////////////////
        // choice diagonal element
        // max in column
        for (int j = i + 1; j < size; ++j) {
            if (a[maxstrcount][i] < a[j][i]) {
                maxstrcount = j;
            }
        }
        if (i != maxstrcount) {
            // change among ourselves str
            std::swap(a[i], a[maxstrcount]);
            mult *= -1;
        }
        /////////////////////////////////////////
        print(a, size);
        /////////////////////////////////////////
        // set zero under diagonal
        for (int j = i + 1; j < size; ++j) {
            const double mult = a[j][i] / a[i][i];
            for (int k = 0; k < size; ++k) {
                a[j][k] -= mult * a[i][k];
            }
        }
        /////////////////////////////////////////
    }
    /////////////////////////////////////////
    double det = 1;
    // multiply elements at diagonal
    for (int i = 0; i < size; ++i) {
        det *= a[i][i];
    }
    return det * mult;
    /////////////////////////////////////////
}
void testing(double** a) {
    a[0][0] = 2.0;
    a[0][1] = 0.0;
    a[0][2] = 1.0;

    a[1][0] = -1.0;
    a[1][1] = 3.0;
    a[1][2] = 1.0;

    a[2][0] = 0.0;
    a[2][1] = 1.0;
    a[2][2] = 0.0;
}
int main() {
    std::cout << std::setprecision(5);
    const int size = 3;
    double** a     = getmemory(size);

    // setrandom(a, size);
    testing(a);

    print(a, size);
    std::cout << getDeterminant(a, size) << std::endl;
    a = deletememory(a, size);
}
