#include <stdio.h>
#include <stdbool.h>

/**
 * Функция проверки числа на простоту
 * @param n проверяемое число
 * @return true если число простое, false в противном случае
 */
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

/**
 * Функция поиска и вывода всех трехзначных простых чисел
 */
void task1_primes() {
    printf("\n--- ЗАДАНИЕ 1: Трехзначные простые числа ---\n");

    int count = 0;
    printf("Все трехзначные простые числа:\n");
    printf("----------------------------------------\n");

    for (int i = 100; i <= 999; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }

    printf("\n----------------------------------------\n");
    printf("Всего найдено: %d простых чисел\n", count);
    printf("----------------------------------------\n");
}