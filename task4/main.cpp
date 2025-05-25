#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

// Проверка на лишнего кандидата
bool ExcessCandCheck(const string input, vector<string> candidates) {
    return find(candidates.begin(), candidates.end(), input) == candidates.end();
}

// Заполнение списка кандидатов
void fill_candidates(istream& is, vector<string>& candidates, int total_candidates) {
    string val;
    for (int i = 0; i < total_candidates; ++i) {
        is >> val;
        candidates.push_back(val);
    }
}

// Заполнение списка избирателя
void fill_votes(istream& is, vector<string>& votelist, int total_candidates, vector<string> candidates) {
    string val;
    for (int i = 0; i < total_candidates; ++i) {
        is >> val;
        if (ExcessCandCheck(val, candidates)) {     // Завершаем выполнение программы в случае выбора несуществующего кандидата
            cout << "Проверьте введеных кандидатов" << endl;
            abort();
        }
        votelist.push_back(val);
    }
}


// Отдельная функция метода Кондорсе
string findCondorsetPair(const string c1, const string c2, const map<int, vector<string>>& votes) {
    int a {}, b {};
    for (auto elem : votes) {
        auto c1_pos = find(elem.second.begin(), elem.second.end(), c1);
        auto c2_pos = find(elem.second.begin(), elem.second.end(), c2);

        if (c1_pos < c2_pos) a++;
        else b++;
    }

    if (a == b) return "NO";
    if (a >= b) return c1;
    return c2;
}


// Метод Борда
void BordaCount(const map<int, vector<string>>& votes, int total_candidates) {
    map<string, int> rating;

    // Тело работы метода Борда
    for (auto vote : votes) {
        int fine {1};
        for (string candidate : vote.second) {
            rating[candidate] += total_candidates - fine;
            fine++;
        }
    }

    // Сортировка по значению
    vector<pair<string, int>> sortedRating(rating.begin(), rating.end());
    sort(sortedRating.begin(), sortedRating.end(),
        [](pair<string, int>& a, pair<string, int>& b) {
            return a.second > b.second;
        });

    if (sortedRating[0].second == sortedRating[1].second) {
        cout << "Определить однозначного победителя невозможно." << endl;
        return ;
    }

    cout << "Победитель: " << sortedRating[0].first << endl;
}


// Метод Кондорсе
void CondorsetMethod(const map<int, vector<string>>& votes, const vector<string>& candidates_list) {
    map<string, int> candPriority;

    for (int i = 0; i < candidates_list.size()-1; ++i) {
        for (int j = i+1; j < candidates_list.size(); ++j) {
            auto win = findCondorsetPair(candidates_list[i], candidates_list[j], votes);
            if (win == "NO") {
                cout << "Победителя по методу Кондорсе не существует" << endl;
                return ;
            }
            candPriority[win]++;
        }
    }

    vector<pair<string, int>> sortedCand(candPriority.begin(), candPriority.end());
    sort(sortedCand.begin(), sortedCand.end(),
        [](pair<string, int>& a, pair<string, int>& b) {
            return a.second > b.second;
        });

    if (sortedCand[0].second == sortedCand[1].second) {
        cout << "Победителя по методу Кондорсе не существует" << endl;
        return ;
    }

    cout << "Победитель: " << sortedCand[0].first << endl;

}


int main() {
    map<int, vector<string>> votes;
    int n {}, k {};     // n - число кандидатов, k - число избирателей
    cout << "Введите число кандитатов (n) и избирателей (k):\t";
    cin >> n >> k;

    vector<string> all_cand;
    cout << "Введите всех кандидатов: ";
    fill_candidates(cin, all_cand, n);
    sort(all_cand.begin(), all_cand.end());

    for (int i = 0; i < k; ++i) {
        printf("Избиратель №%d:\t", i+1);
        fill_votes(cin, votes[i+1],  n, all_cand);
    }

    cout << "\nМетод Борда: \t";
    BordaCount(votes, n);

    cout << "Метод Кондорсе: \t";
    CondorsetMethod(votes, all_cand);

    return 0;
}

