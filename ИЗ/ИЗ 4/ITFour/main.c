#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int getSomeValueFromUser(int min, int max)
{
	int res;
	printf("\nВведите число (Больше %d и меньше %d): ", min, max);
	scanf("%d", &res);
	if ((res <= min) || (res >= max))
	{
		printf("Число некорректно, установлено 1");
		res = 1;
	}
	return res;
}

void powMinPlus(int nums[], int masLen)
{
	for (int index = 0; index < masLen; index++)
	{
		//Отдельная проверка для первого элемента массива
		if (index == 0)
		{
			if (nums[index] < nums[index + 1])
			{
				nums[index] *= nums[index];
			}
			continue;
		}

		//Отдельная проверка для последнего элемента массива
		if (index == (masLen-1))
		{
			if (nums[index] < nums[index - 1])
			{
				nums[index] *= nums[index];
			}
			continue;
		}

		//Проверка для любого другого элемента
		if ((nums[index - 1] > nums[index]) && (nums[index] < nums[index + 1]))
		{
			nums[index] *= nums[index];
			continue;
		}
	}

	//Вывод полученного массива
	for (int index = 0; index < masLen; index++)
	{
		printf("%d ", nums[index]);
	}
}

void powMinMinus(int numses[], int masLen)
{
	int buferOne;
	int buferTwo;
	for (int index = 0; index < masLen; index ++)
	{
		//Запоминаем значение эллемента
		buferOne = numses[index];

		//Отдельная проверка для первого элемента массива
		if (index == 0)
		{
			if (numses[index] < numses[index + 1])
			{
				numses[index] *= numses[index];
			}

			//Сохраняем первоначальное значение элемента
			buferTwo = buferOne;
			continue;
		}

		//Отдельная проверка для последнего элемента массива
		if (index == (masLen - 1))
		{
			if (numses[index] < buferTwo)
			{
				numses[index] *= numses[index];
			}

			//Сохраняем первоначальное значение элемента
			buferTwo = buferOne;
			continue;
		}

		//Проверка для любого другого элемента
		if ((buferTwo > numses[index]) && (numses[index] < numses[index + 1]))
		{
			numses[index] *= numses[index];

			//Сохраняем первоначальное значение элемента
			buferTwo = buferOne;
			continue;
		}

		//Сохраняем первоначальное значение элемента
		buferTwo = buferOne;
	}

	//Вывод полученного массива
	for (int index = 0; index < masLen; index++)
	{
		printf("%d ", numses[index]);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	//Получаем от пользователя максимальную длинну массива
	int masLen = getSomeValueFromUser(0, 1000);

	//Получаем от польователя максимально возможное сгенерированное число)
	int max = getSomeValueFromUser(0, 10000000);

	printf("\n");

	//Генерируем массивы
	int numsPlus[1000];
	int numsMinus[1000];
	for (int index = 0; index < masLen; index++)
	{
		numsPlus[index] = rand()%(max+1);
		numsMinus[index] = numsPlus[index];
		printf("%d ", numsPlus[index]);
	}

	printf("\n");

	//Вызываем функцию на возведение в квадрат локальных минимумов с учётом прошлых возведений
	powMinPlus(&numsPlus[0], masLen);

	printf("\n");

	powMinMinus(&numsMinus[0], masLen);

	return 0;
}