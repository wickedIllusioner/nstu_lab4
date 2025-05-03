#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

bool random_choice() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);

    if (dist(gen) == 0) return false;
    return true;
}

void game_logic(bool player1, bool player2, int& pt1, int& pt2) {
    if (!player1 && !player2) {
        pt1 += 4;
        pt2 += 4;
    }
    else if ( !player1 && player2 )
        pt1 += 20;
    else if (player1 && !player2)
        pt2 += 20;
    else {
        pt1 += 24;
        pt2 += 24;
    }
}

void game(bool (*strat1)(int, vector<bool>&, vector<bool>&),
          bool (*strat2)(int, vector<bool>&, vector<bool>&),
          int rounds) {

    vector<bool> alg1, alg2;
    int pt1 {}, pt2 {};

    for (int round = 0; round < rounds; ++round) {
        auto player1 = strat1(round, alg1, alg2);
        auto player2 = strat2(round, alg2, alg1);
        game_logic(player1, player2, pt1, pt2);
    }

    if (pt1 > pt2)
        cout << "Победил игрок 1! (" << pt1 << " > " << pt2 << ")" << endl;
    else if (pt2 > pt1)
        cout << "Победил игрок 2! (" << pt1 << " < " << pt2 <<")" << endl;
    else {
        cout << "Ничья! (" << pt1 << " = " << pt2 << ")" << endl;
    }
}


// Начинает с сотр. Затем повторяет ход противника наоборот, а после случ.исход
bool algo1(int round_num, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    if (round_num == 0) {
        self_choices.push_back(true);
        return true;
    }

    if (round_num % 2 == 1) {
        bool rand = random_choice();
        self_choices.push_back(rand);
        return rand;
    }

    return !enemy_choices.back();

}

// Начинает с отказа. Если предыдущий ход противника - сотр., то с вероятностью 40% может выбрать сотр. Иначе отказ
bool algo2(int round_num, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    if (round_num == 0) {
        self_choices.push_back(false);
        return false;
    }

    if (enemy_choices.back()) {
        bool decision = (rand() % 100) < 40;
        self_choices.push_back(decision);
        return decision;
    }

    return false;
}

// Первые 5 ходов случайны. Затем идет анализ ходов противника. Больше сотр. -> отказ. Больше отказов -> сотр. Если поровну -> случайный выбор
bool algo3(int round_num, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    if (round_num <= 5) {
        bool rand = random_choice();
        self_choices.push_back(rand);
        return rand;
    }

    int count_true = count(enemy_choices.begin(), enemy_choices.end(), true);
    int count_false = count(enemy_choices.begin(), enemy_choices.end(), false);

    if (count_true > count_false) {
        self_choices.push_back(false);
        return false;
    }
    if (count_true < count_false) {
        self_choices.push_back(true);
        return true;
    }
    if (count_true == count_false) {
        bool rand = random_choice();
        self_choices.push_back(rand);
        return rand;
    }
}

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    minstd_rand rd(seed);
    uniform_int_distribution<> rounds(100, 200);

    return 0;
}
