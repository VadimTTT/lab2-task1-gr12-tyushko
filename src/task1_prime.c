#include <stdio.h>
#include <stdbool.h>

// Функция для проверки, является ли число простым
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void task1_primes() {
    printf("\n--- Задание 1: Трехзначные простые числа ---\n");

    int count = 0;
    printf("Все трехзначные простые числа:\n");

    for (int i = 100; i <= 999; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }

    printf("\nВсего найдено: %d простых чисел\n", count);
}