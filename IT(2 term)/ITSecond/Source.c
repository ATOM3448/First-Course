#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int** matGen(int countOfString, int countOfCollum, int emptyCollums ,short mode)
{
	//mode = 0 - Выделение памяти, без присвоения значений
	//mode = 1 - Выделение памяти, значения присваиваются, не выводятся
	//mode = 2 - Выделение памяти, значения присваиваются, идёт вывод
	//Параметр emptyCollums указывает, сколько столбцов с конца будут пустыми

	int** matrix = malloc(sizeof(int**) * countOfString);
	for (int indexOfString = 0; indexOfString < countOfString; indexOfString++)
	{
		matrix[indexOfString] = malloc(sizeof(int) * (countOfCollum + emptyCollums));
		if (mode == 1)
		{
			for (int indexOfCollum = 0; indexOfCollum < (countOfCollum); indexOfCollum++)
			{
				matrix[indexOfString][indexOfCollum] = rand() % 100;
			}
		}
		if (mode == 2)
		{
			for (int indexOfCollum = 0; indexOfCollum < (countOfCollum); indexOfCollum++)
			{
				matrix[indexOfString][indexOfCollum] = rand() % 100;
				printf("%4d ", matrix[indexOfString][indexOfCollum]);
			}
			printf("\n");
		}
	}
	return matrix;
}

int counting(int** matrix, int numOfCollum, int lenOfCollum, float* secOut)
{
	//Ищем среднее
	float average = 0;
	for (int i = 0; i < lenOfCollum; i++)
	{
		average += matrix[i][numOfCollum];
	}
	average /= lenOfCollum;

	//Ищем числа, которые больше среднего
	int count = 0;
	for (int i = 0; i < lenOfCollum; i++)
	{
		if ((float)matrix[i][numOfCollum] > average)
		{
			count++;
		}
	}

	*secOut = average;
	return count;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	//Получаем размеры матрицы
	int m;
	int n;
	printf("Введите M: ");
	scanf("%d", &m);
	printf("Введите n: ");
	scanf("%d", &n);

	//Генерируем матрицу
	int** matrix = matGen(m, n, 0, 2);

	//Считаем сколько элементов столбце больше среднего этого столбца
	int* res = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) 
	{
		float average;
		res[i] = counting(matrix, i, m, &average);
		printf("\n%d[%f] | %d\n", i+1, average,res[i]);
	}

	getch();
	return 0;
}