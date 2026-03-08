#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

/**
 * Функция ручного ввода данных о ПО
 */
void input_software_manual(struct Software *soft, int index) {
    printf("\n--- Программа №%d ---\n", index + 1);

    printf("Название: ");
    scanf("%s", soft->name);

    printf("Производитель: ");
    scanf("%s", soft->company);

    printf("Год выпуска: ");
    scanf("%d", &soft->release_year);

    printf("Версия: ");
    scanf("%f", &soft->version);

    printf("Период поддержки (лет): ");
    scanf("%d", &soft->support_period);

    printf("Цена (руб): ");
    scanf("%f", &soft->price);
}

/**
 * Функция генерации случайных данных о ПО
 */
void generate_software_random(struct Software *soft, int index) {
    // Названия программ
    char* soft_names[] = {"Antivirus", "Office", "Browser", "Editor", "Player", "CAD"};
    strcpy(soft->name, soft_names[rand() % 6]);

    // Производители
    char* companies[] = {"Microsoft", "Apple", "Google", "Adobe", "Oracle", "IBM"};
    strcpy(soft->company, companies[rand() % 6]);

    soft->release_year = 2015 + rand() % 10;
    soft->version = 1.0 + (rand() % 10) / 2.0;
    soft->support_period = 1 + rand() % 8;
    soft->price = 50 + (rand() % 2000) / 10.0;
}

/**
 * Функция создания массива ПО
 * @param soft массив структур
 * @param max_size максимальный размер
 * @param argc количество аргументов командной строки
 * @param argv массив аргументов командной строки
 * @return фактическое количество созданных записей
 */
int create_software(struct Software soft[], int max_size, int argc, char* argv[]) {
    int n;

    printf("\n--- СОЗДАНИЕ МАССИВА ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ---\n");

    // Проверяем, есть ли аргумент командной строки для размера
    if (argc > 3) {
        n = atoi(argv[3]); // четвертый аргумент
        if (n > max_size) {
            printf("Предупреждение: размер > %d, установлено %d\n", max_size, max_size);
            n = max_size;
        }
        if (n <= 0) n = 5;

        printf("Режим: автоматическая генерация\n");
        printf("Размер массива из командной строки: %d\n", n);
        printf("Генерация случайных данных...\n");

        for (int i = 0; i < n; i++) {
            generate_software_random(&soft[i], i);
        }
    } else {
        printf("Режим: ручной ввод\n");
        printf("Введите количество программ (не более %d): ", max_size);
        scanf("%d", &n);

        if (n > max_size) {
            printf("Превышен максимальный размер! Установлено %d\n", max_size);
            n = max_size;
        }

        for (int i = 0; i < n; i++) {
            input_software_manual(&soft[i], i);
        }
    }

    printf("Создано %d записей о программном обеспечении\n", n);
    return n;
}

/**
 * Функция вывода ПО, дороже 200 руб и с поддержкой более 3 лет
 */
void print_expensive_software(struct Software soft[], int size) {
    printf("\n--- ПО ДОРОЖЕ 200 РУБ И ПОДДЕРЖКА > 3 ЛЕТ ---\n");
    printf("Критерии: цена > 200 руб, поддержка > 3 лет\n");
    printf("------------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < size; i++) {
        if (soft[i].price > 200 && soft[i].support_period > 3) {
            printf("%s (v%.1f) от %s\n", 
                   soft[i].name, soft[i].version, soft[i].company);
            printf("  Год: %d, Цена: %.2f руб, Поддержка: %d лет\n", 
                   soft[i].release_year, soft[i].price, soft[i].support_period);
            printf("------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Программ, удовлетворяющих условиям, не найдено\n");
        printf("------------------------------------------------\n");
    }
}

/**
 * Функция вывода всего ПО (для отладки)
 */
void print_all_software(struct Software soft[], int size) {
    printf("\n--- ВСЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s v%.1f (%s) - %dг, %.2f руб, поддержка %d лет\n",
               i + 1,
               soft[i].name,
               soft[i].version,
               soft[i].company,
               soft[i].release_year,
               soft[i].price,
               soft[i].support_period);
    }
}

/**
 * Основная функция для задания с ПО
 */
void task3_software(int argc, char* argv[]) {
    printf("\n========== ЗАДАНИЕ 4: ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ==========\n");

    struct Software software[MAX_SOFT];
    int count = create_software(software, MAX_SOFT, argc, argv);

    if (count > 0) {
        print_all_software(software, count);
        print_expensive_software(software, count);
    } else {
        printf("Нет данных для обработки\n");
    }

    printf("\n========== ЗАДАНИЕ 4 ВЫПОЛНЕНО ==========\n");
}