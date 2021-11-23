#include <cmath>
#include <iomanip>
#include <iostream>
double func(double x, double y) {
    return cos(sin(y) - x);
}
int main() {
    const double pi  = acos(-1);  // число пи
    const double a   = -1;        // левая граница для икс
    const double b   = 3;         // правая граница для икс
    const double c   = -pi;       // нижняя граница для игрек
    const double d   = pi;        // верхняя граница для игрек
    const double eps = 1e-5;      // точность вычисления

    double resn   = 0;   // ту будет храниться значение интеграла на прошлой итерации
    double resnp1 = 0;   // тут будет храниться значение интеграла на новой итерации
    int N         = 10;  // начальное кол-во разбиений ( со временем увеличивается)

    do {
        resn   = resnp1;  // меняем местами значения интеграла ( для сравнения)
        resnp1 = 0.0;     // зануляем новый интеграл ( будем тут его считать)

        const int n         = N;              // кол-во разбиений вдоль икса
        const int m         = N;              // кол-во разбиений вдоль игрек
        const double deltaX = (b - a) / (n);  // шаг вдоль икса
        const double deltaY = (d - c) / (m);  // шаг вдоль игрек

        for (int i = 0; i < n; ++i) {             // цикл вдоль икса
            for (int j = 0; j < m; ++j) {         // цикл вдоль игрек
                const double x = a + i * deltaX;  // координата левого края ячейки
                const double y = c + j * deltaY;  // координата

                const double xAver = x + deltaX / 2;  // координата икс середины ячейки
                const double yAver = y + deltaY / 2;  // координата игрек середины ячецки

                resnp1 += func(xAver, yAver) * deltaX * deltaY;  // добавляем значение функции в середние ячейки
            }
        }

        std::cout << std::endl << "N = " << N << std::setprecision(10) << "           I = " << resnp1 << std::endl;

        N += 10;  // увеличиваем разбиение

    } while (std::abs(resn - resnp1) > eps);
}
