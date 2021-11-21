#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int detector(int vertLen, int horLen, int matrix[])
{
	//Перебираем все эллементы
	for (int vertIndex = (vertLen - 1); vertIndex >= 0; vertIndex--)
	{
		int flag = 0;
		for (int horIndex = 0; horIndex < horLen; horIndex++)
		{
			//Тк передать в функцию двумерный массив нельзя, выше мы прочитали с указателя данные и записали их в обычный массив 
			//и вместо поиска значений по двум индексам, мы находим нужный эллемент по формуле
			if ((matrix[vertIndex*50+horIndex] % 2 != 0) || (matrix[vertIndex*50+horIndex] == 0))
			{
				flag++;
				break;
			}
		}
		if (flag == 0)
		{
			return vertIndex+1;
			break;
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");

	srand(time(NULL));

	//Получаем кол-во строк, если число не допустимо - ставим дефолт
	int vertLen;
	printf("Введите кол-во строк в матрице(число больше 0 и меньше 51): ");
	scanf("%d", &vertLen);
	if ((vertLen < 1) || (vertLen > 50))
	{
		printf("Число некорректно, установленно значение 25");
		vertLen = 25;
	}

	//Получаем кол-во столбцов, если число не допустимо - ставим дефолт
	int horLen;
	printf("\nВведите кол-во столбцов в матрице(число больше 0 и меньше 51): ");
	scanf("%d", &horLen);
	if ((horLen < 1) || (horLen > 50))
	{
		printf("Число некорректно, установленно значение 25");
		horLen = 25;
	}

	//Объявляем и получаем максимальное число, что мы можем получить при генерации числа, если число не допустимо - устанавливаем дефолт
	int maxValue;
	printf("\nВведите максимально допустимое число, при генерации псевдослучайных чисел, которе больше или равно 0: ");
	scanf("%d", &maxValue);
	if (maxValue < 0)
	{
		printf("Введено недопустимео значение. Установлено 10");
		maxValue = 10;
	}

	//Генерируем матрицу
	int matrix[50][50];
	for (int vertIndex = 0; vertIndex < vertLen; vertIndex++)
	{
		for (int horIndex = 0; horIndex < horLen; horIndex++)
		{
			matrix[vertIndex][horIndex] = rand()%(maxValue + 1);
		}
	}

	//Получаем строку, в случае её отсутствия - 0
	int numberOfResString = detector(vertLen, horLen, &matrix[0][0]);//Передаём указатель на массив, а не массив

	//Вывод, зависимый от номера строки
	if (numberOfResString > 0)
	{
		printf("\nПоследняя строка с чётными числами - %d", numberOfResString);
	}
	else
	{
		printf("\nСтрока с чётными числами отсутсвует");
	}
}