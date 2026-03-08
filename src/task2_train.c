#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRAINS 12
#define DEST_LEN 50
#define TYPE_LEN 20

// Структура TRAIN
struct Train {
    int train_number;           // № поезда
    char destination[DEST_LEN]; // направление
    char arrival_time[6];       // время прибытия (HH:MM)
    char departure_time[6];     // время отбытия (HH:MM)
    int distance;               // расстояние (км)
    int wagon_count;            // количество вагонов
    char wagon_type[TYPE_LEN];  // тип вагона (купейный/плацкарт/люкс)
    int passengers_per_wagon;   // количество пассажиров в вагоне
};

// Функция создания массива поездов
int create_trains(struct Train trains[], int max_size) {
    int n;
    printf("Введите количество поездов (не более %d): ", max_size);
    scanf("%d", &n);

    if (n > max_size) n = max_size;

    for (int i = 0; i < n; i++) {
        printf("\n--- Поезд №%d ---\n", i + 1);

        printf("Номер поезда: ");
        scanf("%d", &trains[i].train_number);

        printf("Направление: ");
        scanf("%s", trains[i].destination);

        printf("Время прибытия (HH:MM): ");
        scanf("%s", trains[i].arrival_time);

        printf("Время отбытия (HH:MM): ");
        scanf("%s", trains[i].departure_time);

        printf("Расстояние (км): ");
        scanf("%d", &trains[i].distance);

        printf("Количество вагонов: ");
        scanf("%d", &trains[i].wagon_count);

        printf("Тип вагона (купейный/плацкарт/люкс): ");
        scanf("%s", trains[i].wagon_type);

        printf("Пассажиров в вагоне: ");
        scanf("%d", &trains[i].passengers_per_wagon);
    }

    return n;
}

// Функция вычисления времени в пути (часы)
int travel_time_hours(struct Train t) {
    int arr_h, arr_m, dep_h, dep_m;
    sscanf(t.arrival_time, "%d:%d", &arr_h, &arr_m);
    sscanf(t.departure_time, "%d:%d", &dep_h, &dep_m);

    int arr_minutes = arr_h * 60 + arr_m;
    int dep_minutes = dep_h * 60 + dep_m;

    if (arr_minutes < dep_minutes) {
        arr_minutes += 24 * 60; // поезд прибывает на следующий день
    }

    return (arr_minutes - dep_minutes) / 60;
}

// Функция вывода поездов в пути более суток
void print_long_trips(struct Train trains[], int size) {
    printf("\n--- Поезда в пути более 24 часов ---\n");
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (travel_time_hours(trains[i]) > 24) {
            printf("Поезд №%d: %s, время в пути %d ч\n", 
                   trains[i].train_number, trains[i].destination, 
                   travel_time_hours(trains[i]));
            found = 1;
        }
    }

    if (!found) printf("Таких поездов нет\n");
}

// Функция суммарного количества пассажиров для купейных вагонов
void total_passengers_compartment(struct Train trains[], int size) {
    int total = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i].wagon_type, "купейный") == 0) {
            total += trains[i].wagon_count * trains[i].passengers_per_wagon;
        }
    }

    printf("\nОбщее количество пассажиров в купейных вагонах: %d\n", total);
}

// Функция вывода поездов в Гродно
void print_trains_to_grodno(struct Train trains[], int size) {
    printf("\n--- Поезда, следующие в Гродно ---\n");
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(trains[i].destination, "Гродно") == 0) {
            printf("Поезд №%d, время прибытия %s\n", 
                   trains[i].train_number, trains[i].arrival_time);
            found = 1;
        }
    }

    if (!found) printf("Поездов в Гродно нет\n");
}

// Функция поиска поезда с максимальным количеством вагонов
void train_max_wagons(struct Train trains[], int size) {
    if (size == 0) return;

    int max_idx = 0;
    for (int i = 1; i < size; i++) {
        if (trains[i].wagon_count > trains[max_idx].wagon_count) {
            max_idx = i;
        }
    }

    printf("\n--- Поезд с максимальным количеством вагонов (%d) ---\n", 
           trains[max_idx].wagon_count);
    printf("Номер: %d, Направление: %s\n", 
           trains[max_idx].train_number, trains[max_idx].destination);
}

void task2_train() {
    printf("\n--- Задание 3: Структура TRAIN ---\n");

    struct Train trains[MAX_TRAINS];
    int count = create_trains(trains, MAX_TRAINS);

    print_long_trips(trains, count);
    total_passengers_compartment(trains, count);
    print_trains_to_grodno(trains, count);
    train_max_wagons(trains, count);
}