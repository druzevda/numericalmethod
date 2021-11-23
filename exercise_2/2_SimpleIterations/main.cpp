#include <cmath>
#include <iostream>
using namespace std;
double f(double x) {
    // исходная функция f(x) = 0
    return sin(x * x) - 6 * x + 1;
}
double phi(double x) {
    //выраженный икс

    // sin(x*x) - 6x +1 = 0
    // sin(x*x) + 1 = 6x
    // x = (sin(x*x) + 1) / 6

    return (sin(x * x) + 1) / 6.0;
}
int main() {
    double eps = 0.0001;  //точность вычислений
    int i      = 1;       // номер итерации

    double xkp1 = 0.0;  // x_0, начальное значение, почти любое
    double xk   = xkp1;

    do {
        xkp1 = phi(xk);  // считаем новый икс с помощью старого

        double temp = xk;  // меняем местами x_k x_k+1
        xk          = xkp1;
        xkp1        = temp;

        cout << "iteration number " << i << " : x = " << xk << std::endl;
        i++;
    } while (abs(xkp1 - xk) > eps);  // критерий остановки

    double x = xk;

    cout << "-----------------------" << endl;
    cout << "x = " << x << endl;         //найденый корень
    cout << "delta = " << f(x) << endl;  // погрешность, по сути, проверочка
}
