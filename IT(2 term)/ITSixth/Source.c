#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Я / я - -33 / -1
//Ю / ю - -34 / -2
//Э / э - -35 / -3
//Ы / ы - -37 / -5
//У / у - -45 / -13
//О / о - -50 / -18
//И / и - -56 / -24
//Е / е - -59 / -27
//А / а - -64 / -32
//Ё / И - -88 / -56


int getCount(char* str)
{
	int count = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] > (-33))
		{
			str[i] -= 32;
		}
		switch (str[i])
		{
		case -33:
			count++;
			break;
		case -34:
			count++;
			break;
		case -35:
			count++;
			break;
		case -37:
			count++;
			break;
		case -45:
			count++;
			break;
		case -50:
			count++;
			break;
		case -56:
			count++;
			break;
		case -59:
			count++;
			break;
		case -64:
			count++;
			break;
		case -88:
			count++;
			break;
		default:
			break;
		}
	}

	return count;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	//Создаём строку
	char str[] = "Шла Саша по шоссе и сосала сушку";

	//Получаем количество гласных
	int count = getCount(&str[0]);

	//Вывод
	printf("%d ", count);

	getch();
	return 0;
}