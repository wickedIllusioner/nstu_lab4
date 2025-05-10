package main

import "fmt"

func task3(x0, a, b, c int) ([]int, int) {
	var sequence []int
	x := x0 // Сохраняем начальное значение для поиска повторения
	sequence = append(sequence, x0)
	period := 0

	for i := 1; i < 15; i++ {
		x0 = (a*x0 + b) % c
		if period == 0 && x == x0 {
			period = i + 1
		}
		sequence = append(sequence, x0)
	}

	return sequence, period
}

func main() {
	var x0, a, b, c int
	fmt.Scanln(&x0, &a, &b, &c)

	seq, idx := task3(x0, a, b, c)
	fmt.Printf("Последовательность: %v\n", seq)
	fmt.Printf("Индекс начала повторения: %d\n", idx)
}

