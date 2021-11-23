#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;
double f1(double x, double y) {  // просто первая функция
    return tan(x * y) - x * x;
}

double f2(double x, double y) {  // просто вторая функция
    return 0.8 * x * x + 2 * y * y - 1.0;
}

double f1x(double x, double y) {  //производная первой функции по икс
    return y / pow(cos(x * y), 2) - 2 * x;
}
double f2x(double x, double y) {  // производная второй функции по икс
    return 1.6 * x;
}

double f1y(double x, double y) {  // производная первой функци по игрек
    return x / std::pow(cos(x * y), 2);
}
double f2y(double x, double y) {  // производная второй функции по игрек
    return 4 * y;
}
void proverka(double x, double y) {  // проверка
    cout << "------------------------------------------" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "------------------------------------------" << endl;
    cout << "f1(x,y) = " << f1(x, y) << "\nf2(x,y) = " << f2(x, y) << endl;
}
int main() {
    int l = 0;  // показатель конец цикла или нет
    int k = 0;  // счетчик итераций

    double x   = 0.4;      // примерный икс ( начальное приближение)
    double y   = 0.2;      // примерный игрек (начальное приближение)
    double eps = 0.00001;  // точность

    do {
        double a = x;  // a = икс на прошлой итерации
        double b = y;  // б = игрек на прошлой итерации

        double J = f1x(a, b) * f2y(a, b) - f1y(a, b) * f2x(a, b);  // якобиан на итерации
        if (J == 0) {                                              // если якобиан нулевой, то ошибка
            cout << "J == 0 " << std::endl;
            exit(0);
        }

        double A = f1(a, b) / J;  // показатель перед дельта икс
        double B = f2(a, b) / J;  // показатель перед дельта игрек

        x = a - A * f2y(a, b) + B * f1y(a, b);  // считаем новый икс
        y = b + A * f2x(a, b) - B * f1x(a, b);  // считаем новый игрек

        if (std::abs(x - a) < eps && std::abs(y - b) < eps) {  // если удовлетворяем критерию остановки
            l = 1;                                             // то закончили
        }
        k++;  // иначе увеличиваем счетчик итераций
        cout << "k = " << k << "\t x = " << x << "\t y = " << y << endl;

    } while (l != 1);

    proverka(x, y);  // проверка
}
