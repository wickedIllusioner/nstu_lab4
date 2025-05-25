#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
const double epsilon = 1e-4;

void print_data(int n, double x1, double x2) {
    cout << "|" << setw(4) << n << " | " << setw(8) << x1 << " | " << setw(8) << x2 << " | " << setw(12) <<  x2-x1 << " |" << endl;
}

double f(double x) {
    return 2*log(x) - 0.5*x + 1;
}

double df(double x) {
    return 2/x - 0.5;
}

double d2f(double x) {
    return -( 2. / (x*x) );
}

double phi(double x) {
    return x - 0.5 * (2 * log(x) - 0.5 * x + 1);
}

double dphi(double x) {
    return 1.25 - 1./x;
}



// Метод половинного значения
void dichotomy(double a, double b) {
    cout << "Метод половинного деления: " << endl;
    int k {0};
    double ck;
    cout << "|" << setw(4) << "N" << " | " << setw(8) << "an" << " | " << setw(8) << "bn" << " | " << setw(12) << "bn-an" << " |" << endl;

    do {
        ck = (a+b) / 2;
        if (f(a) * f(ck) < 0) {
            b = ck;
        } else {
            a = ck;
        }
        k++;
        print_data(k, a, b);
    } while (fabs(b-a) > epsilon);

    cout << "Корень: " << setprecision(6) << (a+b) / 2 << endl;
    cout << "Кол-во итераций: " << k << endl;
    cout << endl;
}


// Метод простых итераций
void simple_iteration(double x0) {
    cout << "Метод простых итераций: " << endl;

    if (abs(dphi(x0)) > 1) {
        cout << "Невозможно применить метод. Выберите другое начальное приближение" << endl;
        return ;
    }

    int k = 0;
    double x1, prev_x;
    cout << "|" << setw(4) << "N" << " | " << setw(8) << "xn" << " | " << setw(8) << "xn1" << " | " << setw(12) << "xn1-xn" << " |" << endl;

    do {
        k++;
        prev_x = x0;
        x1 = phi(x0);
        print_data(k, x0, x1);
        x0 = x1;
    } while (fabs(x1 - prev_x) >= epsilon);

    cout << "Корень: " << setprecision(6) << x1 << endl;
    cout << "Кол-во итераций: " << k << endl;
}


// Метод Ньютона
void newton(double x0) {
    cout << "Метод Ньютона:" << endl;
    if (f(x0) * d2f(x0) <= 0) {
        cout << "Невозможно применить метод. Выберите другое начальное приближение" << endl;
        return ;
    }

    int k {};
    double xk {x0};
    double xk1 = xk - (f(xk) / df(xk));

    cout << "|" << setw(4) << "N" << " | " << setw(8) << "xn" << " | " << setw(8) << "xn1" << " | " << setw(12) << "xn1-xn" << " |" << endl;
    while ( abs(xk1 - xk) >= epsilon) {
        xk = xk1;
        xk1 = xk - (f(xk) / df(xk));
        k++;
        print_data(k, xk, xk1);
    }

    cout << "Корень: " << setprecision(6) << xk1 << endl;
    cout << "Кол-во итераций: " << k << endl;
    cout << endl;
}

int main() {
    dichotomy(0, 1);
    newton(0.5);
    simple_iteration(0.5);

    return 0;
}
