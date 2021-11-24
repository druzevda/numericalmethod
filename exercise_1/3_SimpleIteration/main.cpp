#include <cmath>
#include <iomanip>
#include <iostream>
#define size 4
double** getmemformatrix() {  // get memory for matrix
    double** A = new double*[size];
    for (int i = 0; i < size; ++i) {
        A[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            A[i][j] = 0.0;
        }
    }
    return A;
}
double* getmemforstr() {
    double* B = new double[size];
    for (int i = 0; i < size; ++i) {
        B[i] = 0.0;
    }
    return B;
}
void printsystem(double** A, double* B) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(7) << A[i][j] << ' ';
        }
        std::cout << '\t' << std::setw(7) << B[i] << '\n';
    }
}
void deletematrix(double** A) {
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
    }
    delete[] A;
}
void deletestr(double* B) {
    delete[] B;
}
void delenie(double** A, double* B) {
    for (int i = 0; i < size; ++i) {
        double delitel = A[i][i];
        for (int j = 0; j < size; ++j) {
            A[i][j] = A[i][j] / delitel;
        }
        B[i] = B[i] / delitel;
    }
}
bool stop(double* X_k, double* X_kp, double eps) {
    double delta = 0.0;
    for (int i = 0; i < size; i++) {
        if (std::abs(X_k[i] - X_kp[i]) > delta) {
            delta = std::abs(X_kp[i] - X_k[i]);
        }
    }
    return delta < eps;
}
void ychebnik(double** A, double* B) {
    A[0][0] = 6.9;
    A[0][1] = 0.0319;
    A[0][2] = 0.0039;
    A[0][3] = 0.461;

    A[1][0] = 0.0191;
    A[1][1] = 6.0;
    A[1][2] = 0.0333;
    A[1][3] = 0.0405;

    A[2][0] = 0.0134;
    A[2][1] = 0.0205;
    A[2][2] = 5.1;
    A[2][3] = 0.0348;

    A[3][0] = 0.0077;
    A[3][1] = 0.0149;
    A[3][2] = 0.022;
    A[3][3] = 4.2;

    B[0] = 5.6632;
    B[1] = 6.1119;
    B[2] = 6.2;
    B[3] = 5.9275;
}
void copystr(double* X_k, double* X_kp) {
    for (int j = 0; j < size; ++j) {
        X_k[j] = X_kp[j];
    }
}
void reshala(double** A, double* B, double* X_kp, double eps) {
    double* X_k = getmemforstr();
    do {
        copystr(X_k, X_kp);
        for (int i = 0; i < size; i++) {
            double x_kp_elem = B[i];
            for (int j = 0; j < size; j++) {
                if (i == j) {
                } else {
                    x_kp_elem = x_kp_elem - A[i][j] * X_k[j];
                }
            }
            X_kp[i] = x_kp_elem;
        }
    } while (!stop(X_k, X_kp, eps));
    deletestr(X_k);
}
void printstr(double* X_k) {
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(7) << X_k[i] << '\n';
    }
}
double calcDelta(double** A, double* X, double* B) {
    double maxDelta = 0.0;
    for (int i = 0; i < size; ++i) {
        double newDelta = B[i];
        for (int j = 0; j < size; ++j) {
            newDelta -= A[i][j] * X[j];
        }
        if (std::abs(newDelta) > maxDelta) {
            maxDelta = std::abs(newDelta);
        }
    }
    return maxDelta;
}

int main() {
    // AX-B=0;
    std::cout << std::setprecision(4);

    double** A = getmemformatrix();
    double* B  = getmemforstr();
    double* X  = getmemforstr();

    double eps = 0.0001;

    ychebnik(A, B);
    printsystem(A, B);

    std::cout << "---------------------" << std::endl;
    delenie(A, B);
    printsystem(A, B);

    std::cout << "---------------------" << std::endl;
    reshala(A, B, X, eps);
    printstr(X);

    const double delta = calcDelta(A, X, B);
    std::cout << "max delta = " << delta << std::endl;

    deletestr(B);
    deletestr(X);
    deletematrix(A);
}
