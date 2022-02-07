#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int** genMatrix(int M, int N)
{
	int** mat = malloc(sizeof(int*) * M);
	for (int i = 0; i < M; i++)
	{
		printf("\n");
		mat[i] = malloc(sizeof(int) * N);
		for (int j = 0; j < N; j++)
		{
			mat[i][j] = rand()%5;
			printf("%4d ", mat[i][j]);
		}
	}
	printf("\n");
	return mat;
}

int* nums(int* string, int N, int* size)
{
	//Ищем кол-во различных чисел
	int countOfNums = 1;
	for (int i = 1; i < N; i++)
	{
		int flag = 1;
		for (int j = i-1; j >= 0; j--)
		{
			if (string[i] == string[j])
			{
				flag = 0;
			}
		}
		if (flag)
		{
			countOfNums++;
		}
	}

	//Формируем множество
	int* plenty = malloc(sizeof(int) * countOfNums);
	plenty[0] = string[0];
	int index = 1;
	for (int i = 1; i < N; i++)
	{
		int flag = 1;
		for (int j = i - 1; j >= 0; j--)
		{
			if (string[i] == string[j])
			{
				flag = 0;
			}
		}
		if (flag)
		{
			plenty[index++] = string[i];
		}
	}

	//Сортируем множество
	for (int j = 0; j < countOfNums; j++)
	{
		for (int i = 0; i < (countOfNums - 1); i++)
		{
			if (plenty[i] > plenty[i + 1])
			{
				int buf = plenty[i];
				plenty[i] = plenty[i + 1];
				plenty[i + 1] = buf;
			}
		}
	}

	//Выводим множество
	printf("\n");
	printf("\n");
	for (int i = 0; i < countOfNums; i++)
	{
		printf("%3d", plenty[i]);
	}
	printf("\n");

	*size = countOfNums;
	return plenty;
}

int countingSimilar(int* plenty, int lenghtOfPlenty, int** mat, int M, int N)
{
	//Переменная, отображающая кол-во схожих строк
	int countOfSimilar = 0;

	//Сравниваем все строки
	for (int i = 1; i < M; i++)
	{
		int size;
		int* bufPlenty = nums(mat[i], N, &size);
		if (size != lenghtOfPlenty)
		{
			continue;
		}

		int flag = 1;
		for (int j = 0; j < lenghtOfPlenty; j++)
		{
			if (bufPlenty[j] != plenty[j])
			{
				flag--;
				break;
			}
		}
		if (flag)
		{
			countOfSimilar++;
		}
	}

	
	return countOfSimilar;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	//Ввод размеров
	int M;
	int N;
	printf("Введите M: ");
	scanf("%d", &M);
	printf("Введите N: ");
	scanf("%d", &N);

	//Генерация матрицы
	int** mat = genMatrix(M, N);

	//Формируем множество
	int size;
	int* plenty = nums(mat[0], N, &size);

	//Выявление схожей строки
	printf("\nСхожих строк с первой: %d", countingSimilar(plenty, size, mat, M, N));

	free(mat);
	getch();
	return 0;
}