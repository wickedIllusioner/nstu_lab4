#include <iostream>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

ostream& operator<<(ostream& os, unordered_set<string> uset) {
    for (auto elem : uset)
        os << elem << " ";
    os << endl;

    return os;
}

void fill_candidates(istream& is, unordered_set<string>& candidates, int total_candidates) {
    string val;
    for (int i = 0; i < total_candidates; ++i) {
        is >> val;
        candidates.insert(val);
    }
}


map<string, int> BordaCount(const map<int, unordered_set<string>>& votes, int total_candidates) {
    map<string, int> rating;

    for (auto vote : votes) {
        int fine {1};
        for (string candidate : vote.second) {
            rating[candidate] += total_candidates - fine;
            fine++;
        }
    }

    return rating;
}



int main() {
    map<int, unordered_set<string>> votes;
    int n {}, k {};     // n - число кандидатов, k - число избирателей
    cout << "Введите число кандитатов (n) и избирателей (k):\t";
    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        printf("Избиратель №%d:\t", i+1);
        fill_candidates(cin, votes[i+1],  n);
    }

    // for (auto vote : votes) {
    //     cout << vote.second;
    // }

    // auto borda = BordaCount(votes, n);
    // for (auto elem : borda) {
    //     cout << elem.first << " : " << elem.second << endl;
    // }

    return 0;
}
