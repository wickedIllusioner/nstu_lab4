package main

import (
	"fmt"
	"math"
	"math/rand"
	"slices"
	"sort"
	"strconv"
)

func TaskDivisor(n int) {
	fmt.Printf("Задание №%d:\n", n)
}

// Вычисление среднего значения
func average(sl []float64) (avg float64) {
	for _, v := range sl {
		avg += v
	}
	avg /= float64(len(sl))
	return
}

// Смена порядка первого и последнего разряда четного числа
func SwapDigits(x float64) float64 {
	integer, frac := math.Modf(x)

	numDigits := len(strconv.Itoa(int(integer)))
	lastDigit := int(integer) % 10
	firstDigit := int(integer) / int(math.Pow10(numDigits-1))
	middleDigits := int(integer) % int(math.Pow10(numDigits-1)) / 10

	newNumber := float64(lastDigit*int(math.Pow10(numDigits-1))+middleDigits*10+firstDigit) + frac
	return newNumber
}

// Задание 1
func task1() []float64 {
	var rnd []float64
	for i := 0; i < rand.Intn(1000)+10; i++ {
		rnd = append(rnd, rand.Float64()*100)
	}
	return rnd
}

// Задание 2
func task2(sl []float64) (result float64) {
	avg := average(sl)
	for _, v := range sl {
		result += math.Pow(v, 2) + math.Pow(avg, 2)
	}
	return
}

// Задание 3
func task3(nums []float64) (modified []float64) {
	for _, n := range nums {
		if n < 10 || int(n)%10 == 0 {
			modified = append(modified, n)
		} else if (int(n)%2 == 0) && slices.Index(nums, n)%2 == 1 {
			modified = append(modified, SwapDigits(n))
		} else {
			modified = append(modified, n)
		}
	}
	return
}

// Задание 4
func task4() {
	arr := [5]int{25, 73, 100, 22, 82}
	for i := 0; i < len(arr)-1; i++ {
		tmp := arr[i]
		arr[i] = arr[i+1]
		arr[i+1] = tmp
	}
	fmt.Println(arr)
}

// Задание 5
func task5(nums []int) (map[int]int, []int) {
	frequency := make(map[int]int)
	unique_slice := make([]int, 0)

	for _, elem := range nums {
		frequency[elem]++
		if !slices.Contains(unique_slice, elem) {
			unique_slice = append(unique_slice, elem)
		}
	}
	return frequency, unique_slice
}

func main() {
	TaskDivisor(1)
	fn1 := task1()
	fmt.Println(fn1)

	TaskDivisor(2)
	fn2 := task2(fn1)
	fmt.Println(fn2)

	TaskDivisor(3)
	fn3 := task3(fn1)
	fmt.Println(fn3)

	TaskDivisor(4)
	task4()

	TaskDivisor(5)
	length := rand.Intn(1000) + 50
	arr := make([]int, 0, length)
	for i := 0; i < length; i++ {
		arr = append(arr, rand.Intn(21)-10)
	}
	freq, uniq := task5(arr)
	fmt.Printf("Исходный массив: %v\n", arr)
	fmt.Printf("Массив без повторяющихся элементов: %v\n", uniq)

	fmt.Println("Частота чисел в массиве:")
	keys := make([]int, 0)
	for k := range freq {
		keys = append(keys, k)
	}
	sort.Ints(keys)
	for _, k := range keys {
		fmt.Printf("%d : %d\n", k, freq[k])
	}

}

