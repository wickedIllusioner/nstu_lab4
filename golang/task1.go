package main

import (
	"fmt"
	"math"
)

const (
	epsilon float64 = 1e-4
)

// Функция для печати строк таблицы
func print_data(n int, x1 float64, x2 float64) {
	fmt.Printf("|  %4d  |  %8f  |  %8f  |  %12f  |\n", n, x1, x2, x2-x1)
}

// Нелинейное уравнение
func f(x float64) float64 {
	return 2*math.Log(x) - 0.5*x + 1
}

// Производная функции
func df(x float64) float64 {
	return 2/x - 0.5
}

func d2f(x float64) float64 {
	return -(2.0 / (x * x))
}

// Метод половинного деления
func dichotomy(a, b float64) {
	fmt.Println("Метод половинного деления: ")
	var ck float64
	k := 0
	fmt.Printf("| %4s | %8s |  %8s  | %12s |\n", "N", "an", "bn", "bn-an")

	for math.Abs(a-b) > epsilon {
		ck = (a + b) / 2
		if f(a)*f(ck) < 0 {
			b = ck
		} else {
			a = ck
		}
		k++
		print_data(k, a, b)
	}

	fmt.Printf("Корень: %8f\n", (a+b)/2)
	fmt.Printf("Кол-во итераций: %d\n", k)
	fmt.Println()
}

// Канонический вид исходной функции
func phi(x float64) float64 {
	return 4*math.Log(x) + 2
}

// Метод простых итераций
func simpleIteration(x0 float64) {
	fmt.Println("Метод простых итераций: ")
	var x1, prev_x float64
	k := 0
	fmt.Printf("| %4s | %8s |  %8s  | %12s |\n", "N", "xn", "xn1", "xn1-xn")

	for {
		prev_x = x0
		x1 = phi(x0)
		print_data(k, x0, x1)
		x0 = x1
		k++
		if !(math.Abs(x1-prev_x) >= epsilon) {
			break
		}
	}

	fmt.Printf("Корень: %8f\n", x1)
	fmt.Printf("Кол-во итераций: %d\n", k)
	fmt.Println()
}

// Метод Ньютона
func newton(x0 float64) {
	fmt.Println("Метод Ньютона: ")
	if f(x0)*d2f(x0) <= 0 {
		fmt.Println("Невозможно применить вывод. Введите другое начальное приближение")
		return
	}

	var k int
	xk := x0
	xk1 := xk - (f(xk) / df(xk))
	fmt.Printf("| %4s | %8s |  %8s  | %12s |\n", "N", "xn", "xn1", "xn1-xn")

	for {
		xk = xk1
		xk1 = xk - (f(xk) / df(xk))
		k++
		print_data(k, xk, xk1)

		if !(math.Abs(xk1-xk) >= epsilon) {
			break
		}
	}

	fmt.Printf("Корень: %8f\n", xk1)
	fmt.Printf("Кол-во итераций: %d\n", k)
}

func main() {
	dichotomy(1.0, 12.0)
	simpleIteration(1)
	newton(0.5)
}

