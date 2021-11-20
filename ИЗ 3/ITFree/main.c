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

void findTo(int k, int n, int max)
{
	//Перебираем наборы и числа в каждом наборе
	for (int numberOfKitNumbers = 0; numberOfKitNumbers < k; numberOfKitNumbers++)
	{
		int flag = 0;
		for (int numberOfNumberInKit = 0; numberOfNumberInKit < n; numberOfNumberInKit++)
		{
			//Генерируем число в наборе
			 int num = rand()%(max+1);

			 //Если число = 2, тогда флаг = 1, выводим номер набора(+1 так как для пользователя отчёт от 1) и номер в наборе двойки
			 if (num == 2)
			 {
				 flag = 1;

				 printf("%d - %d\n", numberOfKitNumbers + 1, numberOfNumberInKit + 1);
				 break;
			 }
		}
		//Если флаг = 0, т.е двойка не нашлась, выводим номер набора и 0
		if (flag == 0)
		{
			printf("%d - 0\n", numberOfKitNumbers + 1);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	//Получаем число K
	int k = getSomeValueFromUser(0, 1000);
	
	//Получаем число N
	int n = getSomeValueFromUser(0, 1000);

	//Получаем максимально возомжно число для генерации
	int max = getSomeValueFromUser(0, 1000);

	//Вызываем функцию на вывод индекса двойки
	findTo(k, n, max);

	return 0;
}