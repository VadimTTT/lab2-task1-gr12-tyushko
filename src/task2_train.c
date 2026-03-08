#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRAINS 12
#define DEST_LEN 50
#define TYPE_LEN 20
#define TIME_LEN 6

// Структура TRAIN
struct Train {
    int train_number;               // № поезда
    char destination[DEST_LEN];      // направление
    char arrival_time[TIME_LEN];     // время прибытия (HH:MM)
    char departure_time[TIME_LEN];   // время отбытия (HH:MM)
    int distance;                     // расстояние (км)
    int wagon_count;                  // количество вагонов
    char wagon_type[TYPE_LEN];        // тип вагона
    int passengers_per_wagon;         // пассажиров в вагоне
};

/**
 * Функция ручного ввода данных о поезде
 */
void input_train_manual(struct Train *train, int index) {
    printf("\n--- Поезд №%d ---\n", index + 1);

    printf("Номер поезда: ");
    scanf("%d", &train->train_number);

    printf("Направление: ");
    scanf("%s", train->destination);

    printf("Время прибытия (HH:MM): ");
    scanf("%s", train->arrival_time);

    printf("Время отбытия (HH:MM): ");
    scanf("%s", train->departure_time);

    printf("Расстояние (км): ");
    scanf("%d", &train->distance);

    printf("Количество вагонов: ");
    scanf("%d", &train->wagon_count);

    printf("Тип вагона (купейный/плацкарт/люкс): ");
    scanf("%s", train->wagon_type);

    printf("Пассажиров в вагоне: ");
    scanf("%d", &train->passengers_per_wagon);
}

/**
 * Функция генерации случайных данных о поезде
 */
void generate_train_random(struct Train *train, int index) {
    train->train_number = 1000 + rand() % 9000;

    // Случайное направление
    char* cities[] = {"Минск", "Гродно", "Брест", "Витебск", "Гомель", "Могилев"};
    strcpy(train->destination, cities[rand() % 6]);

    // Случайное время
    sprintf(train->arrival_time, "%02d:%02d", rand() % 24, rand() % 60);
    sprintf(train->departure_time, "%02d:%02d", rand() % 24, rand() % 60);

    train->distance = 100 + rand() % 900;
    train->wagon_count = 5 + rand() % 15;

    // Случайный тип вагона
    int type = rand() % 3;
    if (type == 0) strcpy(train->wagon_type, "купейный");
    else if (type == 1) strcpy(train->wagon_type, "плацкарт");
    else strcpy(train->wagon_type, "люкс");

    train->passengers_per_wagon = 20 + rand() % 30;
}

/**
 * Функция создания массива поездов
 * @param trains массив структур
 * @param max_size максимальный размер
 * @param argc количество аргументов командной строки
 * @param argv массив аргументов командной строки
 * @return фактическое количество созданных записей
 */
int create_trains(struct Train trains[], int max_size, int argc, char* argv[]) {
    int n;

    printf("\n--- СОЗДАНИЕ МАССИВА ПОЕЗДОВ ---\n");

    // Проверяем, есть ли аргумент командной строки для размера
    if (argc > 2) {
        n = atoi(argv[2]); // третий аргумент (после имени программы и выбора задания)
        if (n > max_size) {
            printf("Предупреждение: размер > %d, установлено %d\n", max_size, max_size);
            n = max_size;
        }
        if (n <= 0) n = 5; // значение по умолчанию

        printf("Режим: автоматическая генерация\n");
        printf("Размер массива из командной строки: %d\n", n);
        printf("Генерация случайных данных...\n");

        for (int i = 0; i < n; i++) {
            generate_train_random(&trains[i], i);
        }
    } else {
        printf("Режим: ручной ввод\n");
        printf("Введите количество поездов (не более %d): ", max_size);
        scanf("%d", &n);

        if (n > max_size) {
            printf("Превышен максимальный размер! Установлено %d\n", max_size);
            n = max_size;
        }

        for (int i = 0; i < n; i++) {
            input_train_manual(&trains[i], i);
        }
    }

    printf("Создано %d записей о поездах\n", n);
    return n;
}

/**
 * Функция вычисления времени в пути (в часах)
 */
int calculate_travel_time(struct Train t) {
    int arr_h, arr_m, dep_h, dep_m;
    sscanf(t.arrival_time, "%d:%d", &arr_h, &arr_m);
    sscanf(t.departure_time, "%d:%d", &dep_h, &dep_m);

    int arr_minutes = arr_h * 60 + arr_m;
    int dep_minutes = dep_h * 60 + dep_m;

    // Если прибытие раньше отправления, значит поезд прибывает на следующий день
    if (arr_minutes < dep_minutes) {
        arr_minutes += 24 * 60;
    }

    return (arr_minutes - dep_minutes) / 60;
}

/**
 * Функция вывода поездов, находящихся в пути более суток
 */
void print_long_trips(struct Train trains[], int size) {
    printf("\n--- ПОЕЗДА В ПУТИ БОЛЕЕ 24 ЧАСОВ ---\n");
    int found = 0;

    for (int i = 0; i < size; i++) {
        int travel_time = calculate_travel_time(trains[i]);
        if (travel_time > 24) {
            printf("Поезд №%d: %s -> %s, время в пути: %d ч\n",
                   trains[i].train_number, 
                   trains[i].departure_time,
                   trains[i].arrival_time,
                   travel_time);
            found = 1;
        }
    }

    if (!found) {
        printf("Поездов в пути более суток не найдено\n");
    }
}

/**
 * Функция подсчета общего количества пассажиров в купейных вагонах
 */
void total_passengers_compartment(struct Train trains[], int size) {
    printf("\n--- ПАССАЖИРЫ В КУПЕЙНЫХ ВАГОНАХ ---\n");

    int total = 0;
    int train_count = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i].wagon_type, "купейный") == 0) {
            int train_total = trains[i].wagon_count * trains[i].passengers_per_wagon;
            total += train_total;
            train_count++;
            printf("Поезд №%d: %d вагонов × %d пасс = %d пасс\n",
                   trains[i].train_number,
                   trains[i].wagon_count,
                   trains[i].passengers_per_wagon,
                   train_total);
        }
    }

    printf("------------------------------------\n");
    printf("ВСЕГО в %d поездах: %d пассажиров\n", train_count, total);
}

/**
 * Функция вывода поездов, следующих в Гродно
 */
void print_trains_to_grodno(struct Train trains[], int size) {
    printf("\n--- ПОЕЗДА, СЛЕДУЮЩИЕ В ГРОДНО ---\n");
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i].destination, "Гродно") == 0) {
            printf("Поезд №%d, прибытие %s, отправление %s, %d вагонов\n",
                   trains[i].train_number,
                   trains[i].arrival_time,
                   trains[i].departure_time,
                   trains[i].wagon_count);
            found = 1;
        }
    }

    if (!found) {
        printf("Поездов в Гродно не найдено\n");
    }
}

/**
 * Функция поиска поезда с максимальным количеством вагонов
 */
void find_train_max_wagons(struct Train trains[], int size) {
    printf("\n--- ПОЕЗД С МАКСИМАЛЬНЫМ КОЛИЧЕСТВОМ ВАГОНОВ ---\n");

    if (size == 0) {
        printf("Нет данных о поездах\n");
        return;
    }

    int max_idx = 0;
    for (int i = 1; i < size; i++) {
        if (trains[i].wagon_count > trains[max_idx].wagon_count) {
            max_idx = i;
        }
    }

    printf("Поезд №%d\n", trains[max_idx].train_number);
    printf("Направление: %s\n", trains[max_idx].destination);
    printf("Время прибытия: %s\n", trains[max_idx].arrival_time);
    printf("Время отправления: %s\n", trains[max_idx].departure_time);
    printf("Расстояние: %d км\n", trains[max_idx].distance);
    printf("Количество вагонов: %d\n", trains[max_idx].wagon_count);
    printf("Тип вагонов: %s\n", trains[max_idx].wagon_type);
    printf("Пассажиров в вагоне: %d\n", trains[max_idx].passengers_per_wagon);
    printf("Всего пассажиров: %d\n", 
           trains[max_idx].wagon_count * trains[max_idx].passengers_per_wagon);
}

/**
 * Функция вывода всех поездов (для отладки)
 */
void print_all_trains(struct Train trains[], int size) {
    printf("\n--- ВСЕ ПОЕЗДА ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d. №%d %s %s-%s %dкм %dваг %s %dпасс/ваг\n",
               i + 1,
               trains[i].train_number,
               trains[i].destination,
               trains[i].departure_time,
               trains[i].arrival_time,
               trains[i].distance,
               trains[i].wagon_count,
               trains[i].wagon_type,
               trains[i].passengers_per_wagon);
    }
}

/**
 * Основная функция для задания с поездами
 */
void task2_train(int argc, char* argv[]) {
    printf("\n========== ЗАДАНИЕ 3: СТРУКТУРА TRAIN ==========\n");

    struct Train trains[MAX_TRAINS];
    int count = create_trains(trains, MAX_TRAINS, argc, argv);

    if (count > 0) {
        print_all_trains(trains, count);
        print_long_trips(trains, count);
        total_passengers_compartment(trains, count);
        print_trains_to_grodno(trains, count);
        find_train_max_wagons(trains, count);
    } else {
        printf("Нет данных для обработки\n");
    }

    printf("\n========== ЗАДАНИЕ 3 ВЫПОЛНЕНО ==========\n");
}