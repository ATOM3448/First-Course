#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void output(int** matrix, int m, int n)
{
	//Выводим чётные строки, считая от нуля
	printf("Если считать от нуля: \n");
	for (int i = 0; i < m; i += 2)
	{
		printf("#%d    | ", i);
		for (int j = 0; j < n; j++)
		{
			printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}

	//Выводим чётные строки, считая от единицы
	printf("Если считать от единицы: \n");
	for (int i = 1; i < m; i += 2)
	{
		printf("#%d    | ", i + 1);
		for (int j = 0; j < n; j++)
		{
			printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	//Запрашиваем размеры матрицы
	int m;
	int n;
	printf("Введите M: ");
	scanf("%d", &m);
	printf("Введите N: ");
	scanf("%d", &n);

	//Генерируем матрицу
	int** matrix = malloc(sizeof(int*) * m);
	for (int i = 0; i < m; i++)
	{
		matrix[i] = malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = rand()%100;
		}
	}

	output(matrix, m, n);

	free(matrix);

	getch();
	return 0;
}