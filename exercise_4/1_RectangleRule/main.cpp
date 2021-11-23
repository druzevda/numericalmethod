#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
double f(double x) {  // функция, интеграл которой считаем
    return exp(sin(x));
}
double rectangleRule(const double a, const double b, const int n) {  // метод прямоугольников
    const double delta = (b - a) / n;                                // растояние между ячейками
    double res         = 0.0;                                        // тут будет результат
    for (int i = 0; i < n; ++i) {                                    // пробегаем по всем ячейкам
        res += f(a + i * delta + delta / 2);                         // если средние прямоугольники
        // res += f(a + i * delta + delta );//если правые прямоугольники
        // res += f(a + i * delta );// если левые прямоугольники
    }
    return res * delta;
}
int main() {
    const double a   = 0.0;        // левая граница
    const double b   = 1.0;        // правая граница
    const double eps = 0.0000001;  // требуемая точность вычисления

    cout << setprecision(12);  // чтобы цифор после запятой было много

    int n         = 10;   // начальное разбиение
    double resnp1 = 0.0;  // тут будет храниться интеграл на новой итерации
    double resn   = 0.0;  // тут будет храниться интеграл на старой итерации
    int i         = 0;    // номер итрации
    double delta  = 0.0;  // погрешность

    do {
        resn   = resnp1;                  // запоминаем значение старого интеграла
        resnp1 = rectangleRule(a, b, n);  // считаем новый интеграл
        delta  = abs(resnp1 - resn);      // считаем погрешность

        cout << "i = " << i;                      // выводим номер итерации
        cout << "\t\tN = " << n;                  // выводим число разбиений
        cout << "\t\tI  = " << resnp1;            // выводим на экран
        cout << "\t\tdelta = " << delta << endl;  // выводим погрешность на данном шаге

        i++;     // увеличиваем счетчик итераций
        n *= 2;  // увеличиваем частоту сетки в два раза

    } while (delta > eps);  // критерий остановки( если разница между старым и новый интегралом маленькая, то выходим)
    cout << endl;           // перенос строки
    cout << "integral = " << resnp1 << endl;  // итеговое значение интеграла
    cout << "delta = " << delta << endl;      // итоговая погрешность
}
