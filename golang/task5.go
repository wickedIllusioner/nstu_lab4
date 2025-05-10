package main

import (
	"fmt"
	"math/rand"
	"time"
)

func randomChoice() bool {
	return rand.Intn(2) == 1
}

func gameLogic(player1, player2 bool, pt1, pt2 *int) {
	if !player1 && !player2 {
		*pt1 += 4
		*pt2 += 4
	} else if !player1 && player2 {
		*pt1 += 20
	} else if player1 && !player2 {
		*pt2 += 20
	} else {
		*pt1 += 24
		*pt2 += 24
	}
}

type Strategy func(int, *[]bool, *[]bool) bool

func game(strat1, strat2 Strategy, rounds int) {
	alg1 := make([]bool, 0)
	alg2 := make([]bool, 0)
	pt1, pt2 := 0, 0

	for round := 0; round < rounds; round++ {
		player1 := strat1(round, &alg1, &alg2)
		player2 := strat2(round, &alg2, &alg1)
		gameLogic(player1, player2, &pt1, &pt2)
	}

	if pt1 > pt2 {
		fmt.Printf("Победил игрок 1! (%d > %d)\n", pt1, pt2)
	} else if pt2 > pt1 {
		fmt.Printf("Победил игрок 2! (%d < %d)\n", pt1, pt2)
	} else {
		fmt.Printf("Ничья! (%d = %d)\n", pt1, pt2)
	}
}

// Начинает с сотр. Затем повторяет ход противника наоборот, а после случ.исход
func algo1(roundNum int, selfChoices, enemyChoices *[]bool) bool {
	if roundNum == 0 {
		*selfChoices = append(*selfChoices, true)
		return true
	}

	if roundNum%2 == 1 {
		randChoice := randomChoice()
		*selfChoices = append(*selfChoices, randChoice)
		return randChoice
	}

	if len(*enemyChoices) == 0 {
		return false
	}
	return !(*enemyChoices)[len(*enemyChoices)-1]
}

// Начинает с отказа. Если предыдущий ход противника - сотр., то с вероятностью 40% может выбрать сотр. Иначе отказ
func algo2(roundNum int, selfChoices, enemyChoices *[]bool) bool {
	if roundNum == 0 {
		*selfChoices = append(*selfChoices, false)
		return false
	}

	if len(*enemyChoices) > 0 && (*enemyChoices)[len(*enemyChoices)-1] {
		decision := rand.Intn(100) < 40
		*selfChoices = append(*selfChoices, decision)
		return decision
	}

	*selfChoices = append(*selfChoices, false)
	return false
}

// Первые 5 ходов случайны. Затем идет анализ ходов противника. Больше сотр. -> отказ. Больше отказов -> сотр. Если поровну -> случайный выбор
func algo3(roundNum int, selfChoices, enemyChoices *[]bool) bool {
	if roundNum <= 5 {
		randChoice := randomChoice()
		*selfChoices = append(*selfChoices, randChoice)
		return randChoice
	}

	countTrue := 0
	countFalse := 0
	for _, choice := range *enemyChoices {
		if choice {
			countTrue++
		} else {
			countFalse++
		}
	}

	if countTrue > countFalse {
		*selfChoices = append(*selfChoices, false)
		return false
	}
	if countTrue < countFalse {
		*selfChoices = append(*selfChoices, true)
		return true
	}
	randChoice := randomChoice()
	*selfChoices = append(*selfChoices, randChoice)
	return randChoice
}

func main() {
	rand.Seed(time.Now().UnixNano())
	rounds := rand.Intn(101) + 100 // Генерация числа от 100 до 200

	fmt.Print("1 vs 2: ")
	game(algo1, algo2, rounds)
	fmt.Print("1 vs 3: ")
	game(algo1, algo3, rounds)
	fmt.Print("2 vs 3: ")
	game(algo2, algo3, rounds)
}

