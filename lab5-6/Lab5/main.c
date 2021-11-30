#include <stdlib.h>
#include <stdio.h>
#include <locale.h>


void handlerForTask(int* matrix, int lenOfMatrix)
{
	//Создаём дин. массив и выделяем память
	int *res;
	res = malloc(lenOfMatrix * lenOfMatrix * sizeof(int));

	//Объявляем отдельную переменную индекса, которая будет увеличиваться только при 
	//внесении нового значения в массив res
 	int index = 0;

	//Ищем и заносим отрицательные значения в матрице
	for (int indexOfString = 0; indexOfString < lenOfMatrix; indexOfString++)
	{
		for (int indexOfCollum = 0; indexOfCollum < lenOfMatrix; indexOfCollum++)
		{
			if (matrix[indexOfString * lenOfMatrix + indexOfCollum] < 0)
			{
				res[index] = matrix[indexOfString * lenOfMatrix + indexOfCollum];

				printf("%d ", res[index]);

				index++;
			}
		}
	}

	//Ищем и заносим положительные значения в матрице
	for (int indexOfString = 0; indexOfString < lenOfMatrix; indexOfString++)
	{
		for (int indexOfCollum = 0; indexOfCollum < lenOfMatrix; indexOfCollum++)
		{
			if (matrix[indexOfString * lenOfMatrix + indexOfCollum] >= 0)
			{
				res[index] = matrix[indexOfString * lenOfMatrix + indexOfCollum];

				printf("%d ", res[index]);

				index++;
			}
		}
	}
}

void allValueSetByProgram()
{
	//Создаём и заполняем матрицу
	int matrix[2][2] = 
	{ 
		{2, -10}, 
		{1, -20} 
	};
	int matrixLen = 2;

	//Вызываем обработчик, который переведёт матрицу в массив
	handlerForTask(&matrix[0][0], matrixLen);

}

void allValueSetByUser()
{
	//Запрашиваем размер матрицы
	int lenOfMatrix;
	printf("Для заполненения матрицы M на M введите M: ");
	scanf("%d", &lenOfMatrix);

	if (lenOfMatrix < 2)
	{
		printf("Размер матрицы некорректный. Установлено 3\n");
		lenOfMatrix = 3;
	}
	
	//Создаём дин. массив и выделяем память
	int* matrix;
	matrix = malloc(lenOfMatrix * lenOfMatrix * sizeof(int));

	//Просим пользователя заполнить массив
	for (int indexOfString = 0; indexOfString < lenOfMatrix; indexOfString++)
	{
		for (int indexOfCollum = 0; indexOfCollum < lenOfMatrix; indexOfCollum++)
		{
			scanf("%d", &matrix[indexOfString * lenOfMatrix + indexOfCollum]);
		}
	}

	//Вызываем обработчик, который получит финальный массив
	handlerForTask(&matrix[0], lenOfMatrix);

	//Чистим память от массива, который уже выполнил свою функцию
	free(matrix);
}

void lenOfMasAndMinMaxSetByUser()
{
	//Запрашиваем размер матрицы
	int lenOfMatrix;
	printf("Для заполненения матрицы M на M введите M(число больше 1): ");
	scanf("%d", &lenOfMatrix);

	if (lenOfMatrix < 2)
	{
		printf("Размер матрицы некорректный. Установлено 3\n");
		lenOfMatrix = 3;
	}

	//Создаём дин. массив и выделяем память
	int* matrix;
	matrix = malloc(lenOfMatrix * lenOfMatrix * sizeof(int));

	//Получаем от пользователя максимальные и минимальные значения, которые могут сгенерироваться
	int max;
	printf("Введите максимальное число для генерации(Больше 0): ");
	scanf("%d", &max);
	if (max < 1)
	{
		printf("Введено некорректное число, установлено 10\n");
		max = 10;
	}

	int min;
	printf("Введите минимальное число для генерации(Больше -1 и меньше максимального): ");
	scanf("%d", &min);
	if ((min < 0) || (min >= max))
	{
		printf("Введено некорректное число, установлено max/2\n");
		min = max/2;
	}

	//Заполняем матрицу
	for (int indexOfString = 0; indexOfString < lenOfMatrix; indexOfString++)
	{
		for (int indexOfCollum = 0; indexOfCollum < lenOfMatrix; indexOfCollum++)
		{
			//С помощью генератора псевдослучайных чисел, определяем, какие числа будут положительные, а какие нет
			int mode = 1 + rand() % 2;
			if (mode == 1)
			{
				matrix[indexOfString * lenOfMatrix + indexOfCollum] = min + rand() % max;
				
				printf("%5d ", matrix[indexOfString * lenOfMatrix + indexOfCollum]);
			}
			else
			{
				matrix[indexOfString * lenOfMatrix + indexOfCollum] = -(min + rand() % max);

				printf("%5d ", matrix[indexOfString * lenOfMatrix + indexOfCollum]);
			}
		}
		printf("\n");
	}

	printf("\n");

	//Вызываем обработчик, который получит финальный массив
	handlerForTask(&matrix[0], lenOfMatrix);

	//Чистим память от массива, который уже выполнил свою функцию
	free(matrix);
}

int main()
{
	setlocale(LC_ALL, "rus");

	srand(LC_TIME, "NULL");

	//Узнаём у пользователя, какой он хочет использовать режим программы
	int mode;
	printf("Выберите режим работы:\n\t1. Все значения задаются программой\n\t2. Все значения задаются пользователем\n\t3. Пользователь задаёт только длинну массива и макс и мин ген. числа\n");
	scanf("%d", &mode);

	printf("\n");

	//Проверяем, существует ли данный режим
	if ((mode > 0) && (mode < 4))
	{
		if (mode == 1)
		{
			//Вызываем функцию первого режима, в случае если выбран данный режим
			allValueSetByProgram();
		}

		if (mode == 2)
		{
			//Вызываем функцию второго режима, в случае если выбран данный режим
			allValueSetByUser();
		}

		if (mode == 3)
		{
			//Вызываем функцию третьего режима, в случае если выбран данный режим
			lenOfMasAndMinMaxSetByUser();
		}
	}
	else
	{
		//Если данного режима нет - выводим соответсвующее сообщение
		printf("Введён некорректный режим. Работа программы завершена\n");
	}

	getch();

	return 0;
}