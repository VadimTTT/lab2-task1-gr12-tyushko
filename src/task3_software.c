#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SOFT 20
#define NAME_LEN 50
#define COMPANY_LEN 50

// Структура Software
struct Software {
    char name[NAME_LEN];           // название
    char company[COMPANY_LEN];      // производитель
    int release_year;               // год выпуска
    float version;                   // версия
    int support_period;              // период поддержки (лет)
    float price;                      // цена
};

// Функция создания массива ПО
int create_software(struct Software soft[], int max_size) {
    int n;
    printf("Введите количество программ (не более %d): ", max_size);
    scanf("%d", &n);

    if (n > max_size) n = max_size;

    for (int i = 0; i < n; i++) {
        printf("\n--- Программа №%d ---\n", i + 1);

        printf("Название: ");
        scanf("%s", soft[i].name);

        printf("Производитель: ");
        scanf("%s", soft[i].company);

        printf("Год выпуска: ");
        scanf("%d", &soft[i].release_year);

        printf("Версия: ");
        scanf("%f", &soft[i].version);

        printf("Период поддержки (лет): ");
        scanf("%d", &soft[i].support_period);

        printf("Цена (руб): ");
        scanf("%f", &soft[i].price);
    }

    return n;
}

// Функция вывода ПО по условию
void print_expensive_software(struct Software soft[], int size) {
    printf("\n--- ПО дороже 200 руб и поддержка более 3 лет ---\n");
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (soft[i].price > 200 && soft[i].support_period > 3) {
            printf("%s (%s) - версия %.1f, цена %.2f руб, поддержка %d лет\n",
                   soft[i].name, soft[i].company, soft[i].version,
                   soft[i].price, soft[i].support_period);
            found = 1;
        }
    }

    if (!found) printf("Таких программ нет\n");
}

void task3_software() {
    printf("\n--- Задание 4: Программное обеспечение ---\n");

    struct Software software[MAX_SOFT];
    int count = create_software(software, MAX_SOFT);

    print_expensive_software(software, count);
}