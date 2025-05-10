package main

import (
	"fmt"
	"os"
	"sort"
)

// Проверка на лишнего кандидата
func excessCandCheck(input string, candidates []string) bool {
	for _, cand := range candidates {
		if cand == input {
			return false
		}
	}
	return true
}

// Заполнение списка кандидатов
func fillCandidates(candidates *[]string, totalCandidates int) {
	for i := 0; i < totalCandidates; i++ {
		var val string
		fmt.Scan(&val)
		*candidates = append(*candidates, val)
	}
}

// Заполнение списка избирателя
func fillVotes(votelist *[]string, totalCandidates int, candidates []string) {
	for i := 0; i < totalCandidates; i++ {
		var val string
		fmt.Scan(&val)
		if excessCandCheck(val, candidates) {
			fmt.Println("Проверьте введенных кандидатов")
			os.Exit(1)
		}
		*votelist = append(*votelist, val)
	}
}

// Функция метода Кондорсе для пары кандидатов
func findCondorsetPair(c1, c2 string, votes map[int][]string) string {
	a, b := 0, 0
	for _, vote := range votes {
		c1Pos, c2Pos := -1, -1
		for i, cand := range vote {
			if cand == c1 {
				c1Pos = i
			}
			if cand == c2 {
				c2Pos = i
			}
		}

		if c1Pos < c2Pos {
			a++
		} else {
			b++
		}
	}

	if a == b {
		return "NO"
	}
	if a > b {
		return c1
	}
	return c2
}

// Метод Борда
func bordaCount(votes map[int][]string, totalCandidates int) string {
	rating := make(map[string]int)

	for _, vote := range votes {
		for pos, candidate := range vote {
			rating[candidate] += totalCandidates - pos - 1
		}
	}

	// Сортировка по значению
	type pair struct {
		key   string
		value int
	}
	var sortedRating []pair
	for k, v := range rating {
		sortedRating = append(sortedRating, pair{k, v})
	}

	sort.Slice(sortedRating, func(i, j int) bool {
		return sortedRating[i].value > sortedRating[j].value
	})

	if len(sortedRating) > 1 && sortedRating[0].value == sortedRating[1].value {
		return "Ничья. Определить однозначного победителя невозможно."
	}

	return "Победитель: " + sortedRating[0].key
}

// Метод Кондорсе
func condorsetMethod(votes map[int][]string, candidatesList []string) string {
	candPriority := make(map[string]int)

	for i := 0; i < len(candidatesList)-1; i++ {
		for j := i + 1; j < len(candidatesList); j++ {
			win := findCondorsetPair(candidatesList[i], candidatesList[j], votes)
			if win == "NO" {
				return "Победителя по методу Кондорсе не существует"
			}
			candPriority[win]++
		}
	}

	// Сортировка по значению
	type kv struct {
		key   string
		value int
	}
	var sortedCand []kv
	for k, v := range candPriority {
		sortedCand = append(sortedCand, kv{k, v})
	}

	sort.Slice(sortedCand, func(i, j int) bool {
		return sortedCand[i].value > sortedCand[j].value
	})

	if len(sortedCand) > 1 && sortedCand[0].value == sortedCand[1].value {
		return "Победителя по методу Кондорсе не существует"
	}

	return "Победитель: " + sortedCand[0].key
}

func main() {
	votes := make(map[int][]string)
	var n, k int // n - число кандидатов, k - число избирателей

	fmt.Print("Введите число кандидатов (n) и избирателей (k):\t")
	fmt.Scan(&n, &k)

	var allCand []string
	fmt.Print("Введите всех кандидатов: ")
	fillCandidates(&allCand, n)
	sort.Strings(allCand)

	for i := 0; i < k; i++ {
		fmt.Printf("Избиратель №%d:\t", i+1)
		var vote []string
		fillVotes(&vote, n, allCand)
		votes[i+1] = vote
	}

	fmt.Println("\nМетод Борда: \t", bordaCount(votes, n))
	fmt.Println("Метод Кондорсе: \t", condorsetMethod(votes, allCand))
}

