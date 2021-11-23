#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 genrand(rd());
std::uniform_real_distribution<> dis(1.0, 2.0);

double** getmemformatrix(int size) {  // get memory for matrix
    double** A = new double*[size];
    for (int i = 0; i < size; ++i) {
        A[i] = new double[size];
    }
    return A;
}
double* getmemforstr(int size) {
    double* B = new double[size];
    return B;
}
void randoming(double** A, double* B, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            A[i][j] = dis(genrand);
        }
        B[i] = dis(genrand);
    }
}
void printsystem(double** A, double* B, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(7) << A[i][j] << ' ';
        }
        std::cout << '\t' << std::setw(7) << B[i] << '\n';
    }
}
void deletematrix(double** A, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
    }
    delete[] A;
}
void deletestr(double* B) {
    delete[] B;
}
void sortmatr(double** A, double* B, int size) {
    for (int i = 0; i < size; i++) {
        int maxstrnum = i;
        for (int j = i + 1; j < size; j++) {
            if (A[maxstrnum][i] < A[j][i]) {
                maxstrnum = j;
            }
        }
        std::swap(A[i], A[maxstrnum]);
        std::swap(B[i], B[maxstrnum]);
    }
}
void delenie(double** A, double* B, int size) {
    for (int i = 0; i < size; ++i) {
        double delitel = A[i][i];
        for (int j = 0; j < size; ++j) {
            A[i][j] = A[i][j] / delitel;
        }
        B[i] = B[i] / delitel;
    }
}
bool stop(double* X_k, double* X_kp, int size, double eps) {
    double delta = 0.0;
    for (int i = 0; i < size; i++) {
        if (std::abs(X_k[i] - X_kp[i]) > delta) {
            delta = std::abs(X_kp[i] - X_k[i]);
        }
    }
    return delta < eps;
}
void ychebnik(double** A, double* B) {
    A[0][0] = 4;
    A[0][1] = -1;
    A[0][2] = 1;

    A[1][0] = 2;
    A[1][1] = 6;
    A[1][2] = -1;

    A[2][0] = 1;
    A[2][1] = 2;
    A[2][2] = -3;

    B[0] = 4;
    B[1] = 7;
    B[2] = 0;
}
void copystr(double* X_k, double* X_kp, int size) {
    for (int j = 0; j < size; ++j) {
        X_k[j] = X_kp[j];
    }
}
void reshala(double** A, double* B, double* X_k, double* X_kp, int size, double eps) {
    do {
        copystr(X_k, X_kp, size);
        for (int i = 0; i < size; i++) {
            double x_kp_elem = B[i];
            for (int j = 0; j < size; j++) {
                if (i == j) {
                } else {
                    x_kp_elem = x_kp_elem - A[i][j] * X_kp[j];
                }
            }
            X_kp[i] = x_kp_elem;
        }
    } while (!stop(X_k, X_kp, size, eps));
}
void printstr(double* X_k, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(7) << X_k[i] << '\n';
    }
}

int main() {
    // AX-B=0;
    std::cout << std::setprecision(4);
    const int size = 3;
    double** A     = getmemformatrix(size);
    double* B      = getmemforstr(size);
    double* X_kp   = getmemforstr(size);
    double* X_k    = getmemforstr(size);
    double eps     = 0.0001;
    randoming(A, B, size);
    // ychebnik(A, B);
    printsystem(A, B, size);
    sortmatr(A, B, size);
    std::cout << "---------------------" << std::endl;
    printsystem(A, B, size);
    delenie(A, B, size);
    std::cout << "---------------------" << std::endl;
    printsystem(A, B, size);
    reshala(A, B, X_k, X_kp, size, eps);
    std::cout << "---------------------" << std::endl;
    printstr(X_kp, size);

    deletestr(B);
    deletestr(X_kp);
    deletestr(X_k);
    deletematrix(A, size);
}
