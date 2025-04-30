// ДОДЕЛАТЬ ЗАДАНИЕ 3 !!!

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <map>

using namespace std;

vector<double> func1(unsigned seed) {
    minstd_rand0 rd(seed);
    uniform_int_distribution<> vect(10, 1000);
    uniform_real_distribution<double> dist(0., 100.);

    vector<double> res (vect(rd), 0);
    for (double& elem : res)
        elem = dist(rd);

    return res;
}


double average(const vector<double>& vec) {
    double sum = accumulate(vec.begin(), vec.end(), 0.);
    return sum / vec.size();
}

double func2(const vector<double>& vec) {
    double avg = average(vec);
    double result {};

    for (double elem : vec)
        result += pow(elem, 2) - pow(avg, 2);

    return result;
}

void func4() {
    vector<int> v = {25,73,100,22,82};
    for (int i = 0; i < v.size()-1; ++i) {
        int tmp = v[i];
        v[i] = v[i+1];
        v[i+1] = tmp;
    }

    for (int elem : v) {
        cout << elem << " ";
    }
}

map<int, int> func5(vector<int>& vec) {
    map<int, int> res;

    for (int elem : vec) {
        res[elem]++;
    }

    sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    return res;
}



int main() {
    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();

    auto result1 = func1(seed1);
    // for (auto elem : result1)
    //     cout << elem << " ";

    // ЗАДАНИЕ 5
    vector<int> nums;
    minstd_rand0 rd(seed1);
    uniform_int_distribution<> dist(-10, 10);

    for (int i = 0; i < 50; ++i)
        nums.push_back(dist(rd));

    for (auto elem : nums)
        cout << elem << " ";

    cout << endl;
    auto mm = func5(nums);
    for (auto elem : mm)
        cout << elem.first << " : " << setw(2) <<  elem.second << endl;

    for (auto elem : nums)
        cout << elem << " ";



    return 0;
}
