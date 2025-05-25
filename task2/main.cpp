#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (T elem : v)
        os << elem << " ";
    os << endl;
    return os;
}

// Разделитель между задачами
void TaskDivisor(int n) {
    if (n == 1)
        printf("Задание №%d\n", n);
    else
        printf("\nЗадание №%d\n", n);
}


// Вычисление среднего значения
double average(const vector<double>& vec) {
    double sum = accumulate(vec.begin(), vec.end(), 0.);
    return sum / vec.size();
}

// Смена порядка первого и последнего разряда четного числа
double SwapDigits(double num) {
    // Операция перевода вещественного числа в строковый тип
    stringstream ss;
    ss << num;
    string str_num = ss.str();

    // Поиск индекса знака точки
    auto dot_idx = str_num.find(".");
    string int_part = str_num.substr(0, dot_idx);
    if (str_num.back() != 0) {
        swap(int_part[0], str_num.back());
    }

    string result = int_part + str_num.substr(dot_idx);
    return stod(result);
}


// Задание 1
vector<double> func1(unsigned seed) {
    minstd_rand0 rd(seed);
    uniform_int_distribution<> vect(10, 1000);
    uniform_real_distribution<double> dist(0., 100.);

    vector<double> res (vect(rd), 0);
    for (double& elem : res)
        elem = dist(rd);

    return res;
}

// Задание 2
double func2(const vector<double>& vec) {
    double avg = average(vec);
    double result {};

    for (double elem : vec)
        result += pow(elem, 2) - pow(avg, 2);

    return result;
}

// Задание 3
void func3(vector<double>& vec) {
    for (double& elem : vec) {
        if (elem < 10 || (int)elem % 10 == 0) continue;
        auto n = find(vec.begin(), vec.end(), elem);
        if ((int)(n - vec.begin()) % 2 == 1 && static_cast<int>(elem) % 2 == 0)
            elem = SwapDigits(elem);
    }
}

// Задание 4
void func4() {
    vector<int> v {25,73,100,22,82};
    for (int i = 0; i < v.size()-1; ++i) {
        int tmp = v[i];
        v[i] = v[i+1];
        v[i+1] = tmp;
    }

    for (int elem : v) {
        cout << elem << " ";
    }
    cout << endl;
}

// Задание 5
pair<map<int,int>, vector<int>> func5(const vector<int>& v) {
    map<int, int> frequency;
    vector<int> unique_vec;

    for (int elem : v) {
        frequency[elem]++;
        if ( find(unique_vec.begin(), unique_vec.end(), elem) == unique_vec.end() )
            unique_vec.push_back(elem);
    }

    return make_pair(frequency, unique_vec);
}

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Задание 1
    auto vec = func1(seed);
    TaskDivisor(1);
    cout << vec;

    // Задание 2
    double avg = func2(vec);
    TaskDivisor(2);
    cout << avg << endl;

    // Задание 3
    func3(vec);
    TaskDivisor(3);
    cout << vec;

    // Задание 4
    TaskDivisor(4);
    func4();

    // Задание 5
    TaskDivisor(5);
    vector<int> nums;
    minstd_rand0 rd(seed);
    uniform_int_distribution<> dist(-10, 10);

    for (int i = 0; i < 50; ++i)
        nums.push_back(dist(rd));
    cout << nums;

    auto [frequency, no_repeat] = func5(nums);
    cout << "Массив без повторяющихся элементов: " << endl;
    for (int num : no_repeat)
        cout << num << " ";

    cout << "\nЧастота чисел в массиве: " << endl;
    for (auto pr : frequency) {
        cout << setw(2) <<  pr.first << " : " << setw(2) <<  pr.second << endl;
    }

    return 0;
}
