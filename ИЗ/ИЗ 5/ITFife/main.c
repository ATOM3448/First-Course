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

void addNewZeroInIndex(int nums[], int masLen, int indexOfNewValue)
{
	int buferOne = 0;
	int buferTo;
	for (int index = indexOfNewValue; index <= masLen; index++)
	{
		//Сохраняем текущее значение элемента
		buferTo = nums[index];

		//Заносим новое значение
		nums[index] = buferOne;

		//Устанавливаем число, которое нужно внести в следующем элементе
		buferOne = buferTo;

	}

	//Выводим получившийся массив, для отладки
	for (int index = 0; index <= masLen; index++)
	{
		printf("%d ", nums[index]);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	//Объявляем и получаем от пользователя размер массива
	int masLen = getSomeValueFromUser(0, 1000);

	//Объявляем и получаем от пользователя индекс нового числа(Вычитаем 1, тк пользователь вводит элемент, считая от 1, а не от 0)
	int indexOfNewValue = getSomeValueFromUser(0, masLen+1) - 1;

	//Объявляем и получаем от пользователя максимально возможное число, которое может быть сгенерировано
	int max = getSomeValueFromUser(0, 100000000);

	printf("\n");

	//Генерируем массив
	int nums[1000];
	for (int index = 0; index < masLen; index++)
	{
		nums[index] = rand()%(max + 1);

		//Выводим элементы для отладки
		printf("%d ", nums[index]);
	}

	printf("\n");

	//Добавляем 0 в массив
	addNewZeroInIndex(&nums[0], masLen, indexOfNewValue);

	return 0;
}