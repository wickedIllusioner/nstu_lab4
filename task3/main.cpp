#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T> vec) {
    for (T elem : vec)
        os << elem << " ";
    os << endl;

    return os;
}


pair<vector<int>, int> task3(int x0, int a, int b, int c) {
    pair<vector<int>, int> res;
    int x = x0;     // Сохраняем нулевое значение для дальнейшего сравнения повтора
    res.first.push_back(x0);

    for (int i = 1; i < 15; ++i) {
        x0 = (a * x0 + b) % c;
        if (res.second == 0 && x == x0)
            res.second = i+1;

        res.first.push_back(x0);
    }

    return res;

}


int main() {
    int x0, a, b, c;
    cout << "Введите значения: нач.знач, множитель, инкремент, диапазон" << endl;
    cin >> x0 >> a >> b >> c;

    auto func = task3(x0, a, b, c);
    cout << func.first << func.second;

    return 0;
}
