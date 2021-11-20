#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int boolMessage(int k, int max)
{
	srand(time(NULL));
	int num = rand()%(max+1);
	if (num < k)
	{
		return 1;
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");

	//Получаем число K, если оно некорректно - ставим дефолт
	int k;
	printf("Введите число \"K\" (Больше 1): ");
	scanf("%d", &k);
	if (k < 2)
	{
		printf("Введено некорректное число, установлено 25");
		k = 25;
	}

	//Получаем число N, если оно некорректно - ставим дефолт
	int n;
	printf("\nВведите число \"N\" (Больше 0): ");
	scanf("%d", &n);
	if (n < 1)
	{
		printf("Введено некорректное число, установлено число, равное половине \"K\"");
		n = k/2;
	}

	//Получаем максимально возможное, для генерации число, если оно некорректно - ставим дефолт
	int max;
	printf("\nВведите максимально возможное, для генерации число (Больше 0): ");
	scanf("%d", &max);
	if (max < 1)
	{
		printf("Введено некорректное число, установлено число, равное \"K\"+2");
		max = k+2;
	}

	//Начинаем проверку сгенерированной последовательности.
	for (int i = 0; i < n; i++)
	{
		if (boolMessage(k, max) > 0)
		{
			printf("\nTRUE");
			return 0;
		}
	}
	printf("\nFALSE");

	return 0;
}