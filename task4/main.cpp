#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

// Заполнение списка голосов
void fill_candidates(istream& is, vector<string>& candidates, int total_candidates) {
    string val;
    for (int i = 0; i < total_candidates; ++i) {
        is >> val;
        candidates.push_back(val);
    }
}

// Метод Борда
vector<pair<string, int>>  BordaCount(const map<int, vector<string>>& votes, int total_candidates) {
    map<string, int> rating;

    // Тело работы метода Борда
    for (auto vote : votes) {
        int fine {1};
        for (string candidate : vote.second) {
            rating[candidate] += total_candidates - fine;
            fine++;
        }
    }

    vector<pair<string, int>> sortedRating(rating.begin(), rating.end());
    sort(sortedRating.begin(), sortedRating.end(),
        [](pair<string, int>& a, pair<string, int>& b) {
            return a.second > b.second;
        });


    return sortedRating;
}



int main() {
    map<int, vector<string>> votes;
    int n {}, k {};     // n - число кандидатов, k - число избирателей
    cout << "Введите число кандитатов (n) и избирателей (k):\t";
    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        printf("Избиратель №%d:\t", i+1);
        fill_candidates(cin, votes[i+1],  n);
    }


    auto borda = BordaCount(votes, n);
    if (borda[0].second == borda[1].second) {
        cout << "Определить однозначного победителя невозможно." << endl;
    } else {
        cout << "Победитель: " << borda[0].first << ". Кол-во очков: " << borda[0].second << endl;
    }

    return 0;
}
