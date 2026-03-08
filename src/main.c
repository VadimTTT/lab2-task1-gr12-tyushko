#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Декларации функций
void task1_primes();
void task2_train(int argc, char* argv[]);
void task3_software(int argc, char* argv[]);

int main(int argc, char* argv[]) {
		// Инициализация генератора случайных чисел
		srand(time(NULL));

		int choice;

		printf("========================================\n");
		printf("Лабораторная работа №2\n");
		printf("Вариант 22\n");
		printf("Студент: Тюшко Вадим\n");
		printf("========================================\n");

		printf("\nАргументы командной строки: count = %d\n", argc);
		for (int i = 0; i < argc; i++) {
				printf("  argv[%d] = %s\n", i, argv[i]);
		}

		do {
				printf("\n========== МЕНЮ ==========\n");
				printf("1. Трехзначные простые числа\n");
				printf("2. Структура TRAIN (поезда)\n");
				printf("3. Структура SOFTWARE (ПО)\n");
				printf("0. Выход\n");
				printf("==========================\n");
				printf("Выберите задание: ");
				scanf("%d", &choice);

				switch(choice) {
						case 1:
								task1_primes();
								break;
						case 2:
								task2_train(argc, argv);
								break;
						case 3:
								task3_software(argc, argv);
								break;
						case 0:
								printf("Выход из программы...\n");
								break;
						default:
								printf("Ошибка: неверный выбор! Введите 0-3\n");
				}
		} while(choice != 0);

		return 0;
}