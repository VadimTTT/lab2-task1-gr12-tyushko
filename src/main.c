/* hello.c */
#include <stdio.h>

void main (void)
{
	printf ("Hello World\n");
	printf ("Goodbye World\n");
}
#include <stdio.h>
#include <stdlib.h>

// Декларации функций из других файлов
void task1_primes();
void task2_train();
void task3_software();

int main() {
		int choice;

		do {
				printf("\n========== МЕНЮ ==========\n");
				printf("1. Трехзначные простые числа\n");
				printf("2. Структура TRAIN (поезда)\n");
				printf("3. Структура SOFTWARE (ПО)\n");
				printf("0. Выход\n");
				printf("Выберите задание: ");
				scanf("%d", &choice);

				switch(choice) {
						case 1:
								task1_primes();
								break;
						case 2:
								task2_train();
								break;
						case 3:
								task3_software();
								break;
						case 0:
								printf("Выход...\n");
								break;
						default:
								printf("Неверный выбор!\n");
				}
		} while(choice != 0);

		return 0;
}