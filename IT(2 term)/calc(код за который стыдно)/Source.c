#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void findingErrors(char* input)
{
	//Функция предназначена для нахождения ошибок в заданном выражении(проверяем по 3 раза, на всякий случай)
	for (int hgh = 0; hgh < 3; hgh++)
	{
		//Первая проверка посвященна проверке, на лишние символы(помимо 0-9 - + * ( ) )
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (!(((input[i] >= '0') && (input[i] <= '9')) || (input[i] == '-') || (input[i] == '+') || (input[i] == '*') || (input[i] == '(') || (input[i] == ')')))
			{
				for (int j = i;; j++)
				{
					input[j] = input[j + 1];
					if (input[j + 1] == '\0')
					{
						input[j + 1] = 'NULL';
						break;
					}
				}
				i -= 2;
			}
		}

		//Вторая проверка на дубликаты операций
		for (int i = 0; input[i] != '\0'; i++)
		{
			if ((((input[i] == '*') || (input[i] == '+')) && ((input[i + 1] == '*') || (input[i + 1] == '+'))) || ((input[i] == '-') && (input[i + 1] == '-')))
			{
				for (int j = i;; j++)
				{
					input[j] = input[j + 1];
					if (input[j + 1] == '\0')
					{
						input[j + 1] = 'NULL';
						break;
					}
				}
				i -= 2;
			}
		}

		//Далее проверка на лишние скобки
		//Считаем сколько открывающих/закрывающих
		int cl = 0;
		int op = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == '(')
			{
				op++;
			}
			if (input[i] == ')')
			{
				cl++;
			}
		}

		//Создаём матрицу, котороя состоит из пар индексов открывающих и закрывающих скобок
		int** pairs = malloc(sizeof(int*) * op);
		for (int i = 0; i < op; i++)
		{
			pairs[i] = malloc(sizeof(int) * 2);
		}
		int indOfStrFPair = 0;
		int indOfColFPair = 0;
		int countOfExtra = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == '(')
			{
				int countOfCl = 0;
				int countOfOp = 0;
				int flag = 1;
				for (int j = i; input[j] != '\0'; j++)
				{
					if (input[j] == '(')
					{
						countOfOp++;
					}
					if (input[j] == ')')
					{
						countOfCl++;
					}
					if ((input[j] == ')') && (countOfCl == countOfOp))
					{
						pairs[indOfStrFPair][indOfColFPair++] = i;
						pairs[indOfStrFPair++][indOfColFPair--] = j;
						flag = 0;
						break;
					}
				}
				if (flag)
				{
					countOfExtra++;
				}
			}
		}

		//Чистим лишние пары
		int countOfPairs = op - countOfExtra;
		int** finalPairs = malloc(sizeof(int*) * countOfPairs);
		for (int i = 0; i < countOfPairs; i++)
		{
			finalPairs[i] = malloc(sizeof(int) * 2);
			finalPairs[i][0] = pairs[i][0];
			finalPairs[i][1] = pairs[i][1];
		}
		for (int i = 0; i < op; i++)
		{
			free(pairs[i]);
		}
		free(pairs);

		//Сортируем матрицу так, чтобы в 1 строке у нас была пара индексов Открыл-Закрыл, минуя скобки, которые к этой паре не относятся
		int countOfDel = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if ((input[i] == '(') || (input[i] == ')'))
			{
				int flag = 1;
				for (int j = 0; j < countOfPairs; j++)
				{
					if (((i + countOfDel) == finalPairs[j][0]) || ((i + countOfDel) == finalPairs[j][1]))
					{
						flag = 0;
						break;
					}
				}
				if (flag)
				{
					for (int j = i;; j++)
					{
						input[j] = input[j + 1];
						if (input[j + 1] == '\0')
						{
							i -= 2;
							countOfDel++;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < countOfPairs; i++)
		{
			free(finalPairs[i]);
		}
		free(finalPairs);


		//Проверка на верное расположение операций(чтобы не было ситуаций по типу 100+200-())
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (((input[i] == '-') || (input[i] == '*') || (input[i] == '+')) && (input[i + 1] == ')'))
			{
				for (int j = i;; j++)
				{
					input[j] = input[j + 1];
					if (input[j + 1] == '\0')
					{
						input[j + 1] = 'NULL';
						break;
					}
				}
			}

			if ((input[i] == '(') && ((input[i + 1] == '-') || (input[i + 1] == '*') || (input[i + 1] == '+')))
			{
				if (input[i + 1] == '-')
				{
					if ((input[i + 2] == '-') || (input[i + 2] == '*') || (input[i + 2] == '+'))
					{
						for (int j = i;; j++)
						{
							input[j] = input[j + 1];
							if (input[j + 1] == '\0')
							{
								input[j + 1] = 'NULL';
								break;
							}
						}
						i -= 2;
					}
				}
				else
				{
					for (int j = i;; j++)
					{
						input[j] = input[j + 1];
						if (input[j + 1] == '\0')
						{
							input[j + 1] = 'NULL';
							break;
						}
					}
					i -= 2;
				}
			}

			if ((input[i + 1] == '\0') && ((input[i] == '-') || (input[i] == '*') || (input[i] == '+')))
			{
				for (int j = i;; j++)
				{
					input[j] = input[j + 1];
					if (input[j + 1] == '\0')
					{
						input[j + 1] = 'NULL';
						break;
					}
				}
				i -= 2;
			}

			if (((input[i] < '0') && (input[i] > '9') && (i == 0)) && ((input[i + 1] == '-') || (input[i + 1] == '*') || (input[i + 1] == '+')))
			{
				if (input[i + 1] == '-')
				{
					if ((input[i + 2] == '-') || (input[i + 2] == '*') || (input[i + 2] == '+'))
					{
						for (int j = i;; j++)
						{
							input[j] = input[j + 1];
							if (input[j + 1] == '\0')
							{
								input[j + 1] = 'NULL';
								break;
							}
						}
						i -= 2;
					}
				}
				else
				{
					for (int j = i;; j++)
					{
						input[j] = input[j + 1];
						if (input[j + 1] == '\0')
						{
							input[j + 1] = 'NULL';
							break;
						}
					}
					i -= 2;
				}
			}
		}

		//Очередная проверка на совпадение скобок, тк после прошлой операции, ситуация могла поменяться
		//Здесь был какой-то комент, но я в душе не ебу что здесь было написано до того как сбились коменты, если вы нашли что стоит здесь написать - напишите мне
		countOfPairs = 0;
		for (int k = 0; input[k] != '\0'; k++)
		{
			if (input[k] == '(')
			{
				countOfPairs++;
			}
		}
		pairs = malloc(sizeof(int*) * countOfPairs);
		for (int i = 0; i < countOfPairs; i++)
		{
			pairs[i] = malloc(sizeof(int) * 2);
		}
		indOfStrFPair = 0;
		indOfColFPair = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == '(')
			{
				int countOfCl = 0;
				int countOfOp = 0;
				for (int j = i; input[j] != '\0'; j++)
				{
					if (input[j] == '(')
					{
						countOfOp++;
					}
					if (input[j] == ')')
					{
						countOfCl++;
					}
					if ((input[j] == ')') && (countOfCl == countOfOp))
					{
						pairs[indOfStrFPair][indOfColFPair++] = i;
						pairs[indOfStrFPair++][indOfColFPair--] = j;
						break;
					}
				}
			}
		}
		
		//Проверка на наличие операцй +/* внутри скобок, иначе удаляем их(скобки)
		int countOfDelS = 0;
		for (int i = 0; i < countOfPairs; i++)
		{
			int flag = 1;
			for (int j = (pairs[i][0] - countOfDelS); j < (pairs[i][1] - countOfDelS); j++)
			{
				if ((input[j] == '+') || (input[j] == '*'))
				{
					flag--;
					break;
				}
			}
			if (flag)
			{
				for (int j = (pairs[i][0] - countOfDelS); input[j - 1] != '\0'; j++)
				{
					input[j] = input[j + (pairs[i][1] - pairs[i][0] + 1)];
				}
				countOfDelS += (pairs[i][1] - pairs[i][0]) + 1;
				for (int j = i + 1; j < countOfPairs; j++)
				{
					if ((pairs[j][0] > pairs[i][0]) && (pairs[j][0] < pairs[i][1]))
					{
						i++;
					}
				}
			}
		}
		for (int i = 0; i < countOfPairs; i++)
		{
			free(pairs[i]);
		}
		free(pairs);

		//Проерка на наличие символа умножения перед(иногда после) символами '-' || '(' || ')', если нет - добавляем
		for (int i = 1; input[i] != '\0'; i++)
		{
			if (((input[i] == '-') || (input[i] == '(')) && ((input[i - 1] != '-') && (input[i - 1] != input[i]) && (input[i - 1] != '+') && (input[i - 1] != '*') && (input[i - 1] != '(')))
			{
				char bufOne = '*';
				char bufSec = input[i];
				for (int j = i; input[j - 1] != '\0'; j++)
				{
					bufSec = input[j];
					input[j] = bufOne;
					bufOne = bufSec;
				}
			}
			if ((input[i] == ')') && ((input[i + 1] != '+') && (input[i + 1] != '*') && (input[i + 1] != input[i]) && (input[i + 1] != '\0')))
			{
				char bufOne = '*';
				char bufSec = input[i];
				for (int j = i + 1; input[j - 1] != '\0'; j++)
				{
					bufSec = input[j];
					input[j] = bufOne;
					bufOne = bufSec;
				}
			}
		}
	}
}

char* operationOfSum(char* expression)
{
	//Функция посвященная сумме чисел
	//Для начала ищем индекс плюса(также считаем размер выражения)
	int indexOfPlus = 0;
	int sizeOfString = 1;
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == '+')
		{
			indexOfPlus = i;
		}
		sizeOfString++;
	}

	//Выделяем память под ответ
	char* output = malloc(sizeof(char) * sizeOfString + 1);
	output[sizeOfString] = '\0';
	//Заполняем ответ спецсимволами(для удобства обработки)
	for (int i = 0; i < sizeOfString; i++)
	{
		output[i] = '?';
	}

	//Делим выражение на 2 части: до и после "+"
	int counts[2];
	counts[0] = indexOfPlus;
	counts[1] = sizeOfString - indexOfPlus - 2;

	char** nums = malloc(sizeof(char*) * 2);
	for (int i = 0; i < 2; i++)
	{
		nums[i] = malloc(sizeof(char) * (counts[i] + 1));
	}

	for (int i = 0; i < counts[0]; i++)
	{
		nums[0][i] = expression[i];
	}
	nums[0][counts[0]] = '\0';

	for (int i = 0; i < counts[1]; i++)
	{
		nums[1][i] = expression[i + indexOfPlus + 1];
	}
	nums[1][counts[1]] = '\0';

	//Удаляем минуса, заодно вычисляем режим. 0 - сложение положительных чисел, 1 - сложение отрицательного с положительным, 2 - оба отрицательные
	int mode = 0;
	int indOfNNum;
	if (nums[0][0] == '-')
	{
		mode++;
		indOfNNum = 0;
	}
	if (nums[1][0] == '-')
	{
		mode++;
		indOfNNum = 1;
	}

	//Складываем, в зависимости от режима
	switch (mode)
	{
	case 0:
	{
		int buf = 0;
		for (int i = 0; (i < (counts[1] < counts[0] ? counts[0] : counts[1])) || (buf != 0); i++)
		{
			int numOne = nums[0][counts[0] - 1 - i] - 48;
			int numSec = nums[1][counts[1] - 1 - i] - 48;

			if (((numOne < 0) || (numOne > 9)) || ((counts[0] - 1 - i) < 0))
			{
				numOne = 0;
			}
			if (((numSec < 0) || (numSec > 9)) || ((counts[1] - 1 - i) < 0))
			{
				numSec = 0;
			}

			int res = numOne + numSec + buf;
			buf = 0;
			if (res > 9)
			{
				res -= 10;
				buf = 1;
			}
			output[sizeOfString - 1 - i] = res + 48;
		}
		break;
	}
	case 1:
	{
		//Узнаем какое число больше
		int indOfBigger = 2;
		int indOfSmaller = 2;
		int indOfNotNNum = (indOfNNum == 0 ? 1 : 0);
		if ((counts[indOfNotNNum] > (counts[indOfNNum] - 1)) && (nums[indOfNotNNum][0] != '0'))
		{
			indOfBigger = indOfNotNNum;
			indOfSmaller = indOfNNum;
		}
		if ((counts[indOfNotNNum] < (counts[indOfNNum] - 1)) && (nums[indOfNNum][1] != '0'))
		{
			indOfBigger = indOfNNum;
			indOfSmaller = indOfNotNNum;
		}
		if (counts[indOfNotNNum] == (counts[indOfNNum] - 1))
		{
			for (int i = 0; i < counts[indOfNotNNum]; i++)
			{
				if (nums[indOfNotNNum][i] < nums[indOfNNum][i + 1])
				{
					indOfBigger = indOfNNum;
					indOfSmaller = indOfNotNNum;
					break;
				}
				if (nums[indOfNotNNum][i] > nums[indOfNNum][i + 1])
				{
					indOfBigger = indOfNotNNum;
					indOfSmaller = indOfNNum;
					break;
				}
			}
		}
		if (indOfBigger == 2)
		{
			output[0] = '0';
			output[1] = '\n';
			free(nums[0]);
			free(nums[1]);
			free(nums);
			return output;
		}

		//Складываем
		int finalInd = 0;
		for (int i = 0; i < counts[indOfBigger]; i++)
		{
			int numOne = nums[indOfBigger][counts[indOfBigger] - 1 - i] - 48;
			int numSec = nums[indOfSmaller][counts[indOfSmaller] - 1 - i] - 48;

			if ((numSec < 0) || (numSec > 9))
			{
				numSec = 0;
			}
			if ((numOne < 0) || (numOne > 9))
			{
				numOne = 0;
			}

			int res = numOne - numSec;

			if (res < 0)
			{
				res += 10;
				int indOfDonor = i + 1;
				for (int j = i + 1; nums[indOfBigger][j] == '0'; j++)
				{
					nums[indOfBigger][counts[indOfBigger] - 1 - j] += 9;
					indOfDonor = j;
				}
				nums[indOfBigger][counts[indOfBigger] - 1 - indOfDonor] -= 1;
			}

			output[sizeOfString - 1 - i] = res + 48;
			finalInd = i;
		}

		//Если число, которое больше, являлось отрицательным - добавляем минус
		if (indOfBigger == indOfNNum)
		{
			output[sizeOfString - 2 - finalInd] = '-';
		}

		break;
	}
	case 2:
	{
		int buf = 0;
		int finalInd = 0;
		for (int i = 0; (i < (counts[1] < counts[0] ? counts[0] : counts[1])) || (buf != 0); i++)
		{
			int numOne = nums[0][counts[0] - 1 - i] - 48;
			int numSec = nums[1][counts[1] - 1 - i] - 48;

			if ((numSec < 0) || (numSec > 9))
			{
				numSec = 0;
			}
			if ((numOne < 0) || (numOne > 9))
			{
				numOne = 0;
			}

			int res = numOne + numSec + buf;
			buf = 0;
			if (res > 9)
			{
				res -= 10;
				buf = 1;
			}
			output[sizeOfString - 1 - i] = res + 48;
			finalInd = i;
		}
		output[sizeOfString - 2 - finalInd] = '-';
		break;
	}
	}

	//Удаляем  спецсимволы
	while (output[0] == '?')
	{
		for (int i = 0; output[i] != '\0'; i++)
		{
			output[i] = output[i + 1];
		}
	}

	int flag = 0;

	for (int i = 0; output[i] != '\0'; i++)
	{
		if (output[i] == '-')
		{
			continue;
		}
		if ((output[i] > '0') && (output[i] <= '9'))
		{
			flag++;
			break;
		}
	}

	if (flag)
	{
		if (output[0] == '-')
		{
			while (output[1] == '0')
			{
				for (int i = 1; output[i] != '\0'; i++)
				{
					output[i] = output[i + 1];
				}
			}
		}
		if (output[0] == '0')
		{
			while (output[0] == '0')
			{
				for (int i = 0; output[i] != '\0'; i++)
				{
					output[i] = output[i + 1];
				}
			}
		}
	}
	else
	{
		output[0] = '0';
		output[1] = '\0';
	}

	//Чистим память, которая уже не будет использоваться 
	free(nums[1]);
	free(nums[0]);
	free(nums);
	return output;
}

char* operationOfMultip(char* input)
{
	//Функция для умножения чисел 
	//Считаем количество минусов
	int countOfMinus = 0;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '-')
		{
			countOfMinus++;
			for (int k = i; input[k - 1] != '\0'; k++)
			{
				input[k] = input[k + 1];
			}
			i = -2;
		}
	}

	//Ищем индекс звезды
	int indexOfStar = 0;
	int sizeOfString = 1;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '*')
		{
			indexOfStar = i;
		}
		sizeOfString++;
	}

	//Делим выражение на до/после *
	int counts[2];
	counts[0] = indexOfStar;
	counts[1] = sizeOfString - indexOfStar - 2;

	char** nums = malloc(sizeof(char*) * 2);
	nums[0] = malloc(sizeof(char) * (counts[0] + 1));
	nums[1] = malloc(sizeof(char) * (counts[1] + 1));

	for (int i = 0; i < counts[0]; i++)
	{
		nums[0][i] = input[i];
	}
	nums[0][counts[0]] = '\0';

	for (int i = 0; i < counts[1]; i++)
	{
		nums[1][i] = input[i + indexOfStar + 1];
	}
	nums[1][counts[1]] = '\0';

	//Убираем нули вначале(если они есть)
	for (int l = 0; l < 2; l++)
	{
		while (nums[l][0] == '0')
		{
			for (int i = 0; nums[l][i] != '\0'; i++)
			{
				nums[l][i] = nums[l][i + 1];
			}
			counts[l]--;
		}
	}
	for (int l = 0; l < 2; l++)
	{
		if (counts[l] == 0)
		{
			nums[l][0] = '0';
			nums[l][1] = '\0';
			counts[l]++;
		}
	}

	//Узнаём какое число наибольшее, для удобных вычислений
	int indOfBigger = 0;
	int indOfSmaller = 0;
	if (counts[0] < counts[1])
	{
		indOfBigger = 1;
		indOfSmaller = 0;
	}
	else
	{
		indOfBigger = 0;
		indOfSmaller = 1;
	}

	//Выделяем память для результатов
	//В них мы будем записывать наши промежуточные вычисления
	//Так же заполняем их спецсимволами
	char** results = malloc(sizeof(char*) * counts[indOfSmaller]);
	for (int i = 0; i < counts[indOfSmaller]; i++)
	{
		results[i] = malloc(sizeof(char) * (counts[indOfBigger] + 2));
		for (int j = 0; j < (counts[indOfBigger] + 1); j++)
		{
			results[i][j] = '0';
		}
		for (int j = 0; j < counts[indOfSmaller]; j++)
		{
			results[i][counts[indOfBigger] + 1] = '\0';
		}
	}

	char* expression = malloc(1);
	free(expression);

	//Умножаем числа по следующей схеме:
	//Мы берём наибольшее число и умножаем его на кажду цифру из числа наименьшего, начинаем брать цифры справа, затем умножаем результат на 10^x
	//Каждый раз, когда мы берём новую цифру слева, мы увеличиваем x на 1, изначально x = 0;(x не используется в коде, переменная условна)
	//Когда мы перемножили столько сколько потребуется, мы складываем наши результаты, с помощью функции сложения, перед этим сгенерировав expression
	for (int i = 0; i < counts[indOfSmaller]; i++)
	{
		int secondNum = nums[indOfSmaller][counts[indOfSmaller] - i - 1] - 48;
		int countOfZeroToAdd = 0;
		for (int j = 0; j < counts[indOfBigger]; j++)
		{
			int firstNum = nums[indOfBigger][counts[indOfBigger] - j - 1] - 48;
			int numInRes = results[i][counts[indOfBigger] - j - 1] - 48;

			int res = firstNum * secondNum + numInRes;

			int lon = 1;
			if (res > 9)
			{
				lon = 2;
			}

			char* bufNum = malloc(sizeof(char) * (countOfZeroToAdd + lon + 1));

			if (lon == 1)
			{
				bufNum[0] = res + 48;
				bufNum[1] = '\0';
			}
			if (lon == 2)
			{
				bufNum[0] = (res / 10) + 48;
				bufNum[1] = (res % 10) + 48;
				bufNum[2] = '\0';
			}

			for (int o = 0; o < countOfZeroToAdd; o++)
			{
				bufNum[lon + o] = '0';
			}
			bufNum[lon + countOfZeroToAdd] = '\0';

			countOfZeroToAdd++;

			expression = malloc(sizeof(char) * ((counts[indOfBigger] * 2) + lon + 3));

			expression[0] = '\0';

			strcpy(expression, results[i]);
			strcat(expression, "+");
			strcat(expression, bufNum);

			char* lastBuf = operationOfSum(expression);

			int sizeOfLastBuf = 0;
			for (int k = 0; lastBuf[k] != '\0'; k++)
			{
				sizeOfLastBuf++;
			}

			for (int k = 0; k <= sizeOfLastBuf; k++)
			{
				results[i][counts[indOfBigger] - k + 1] = lastBuf[sizeOfLastBuf - k];
			}
			free(lastBuf);
			free(bufNum);
			free(expression);
		}
	}
	//Создаём финальный ответ
	char* output = malloc(sizeof(char) * 2);
	output[0] = '0';
	output[1] = '\0';

	int zeroToAdd = 0;
	for (int k = 0; k < counts[indOfSmaller]; k++)
	{
		char* bufOfRes = malloc(sizeof(char) * (counts[indOfBigger] + 2 + zeroToAdd));
		for (int i = 0; i < (counts[indOfBigger] + 1 + zeroToAdd); i++)
		{
			bufOfRes[i] = '0';
		}
		bufOfRes[counts[indOfBigger] + 1 + (zeroToAdd++)] = '\0';

		for (int i = 0; i < (counts[indOfBigger] + 1); i++)
		{
			bufOfRes[counts[indOfBigger] - i] = results[k][counts[indOfBigger] - i];
		}
		expression = malloc(sizeof(char) * (counts[indOfBigger] + 2 + zeroToAdd + 1 + counts[indOfSmaller] + counts[indOfBigger] + 1));
		expression[0] = '\0';
		strcpy(expression, bufOfRes);
		strcat(expression, "+");
		strcat(expression, output);
		free(output);
		output = operationOfSum(expression);
		free(bufOfRes);
	}

	//Чистим то, что ещё не почистили, а так же ставим минус в ответ, если он нужен
	free(nums[0]);
	free(nums[1]);
	free(nums);
	for (int i = 0; i < (counts[indOfSmaller]); i++)
	{
		free(results[i]);
	}
	free(results);
	free(expression);

	char b = '-';
	char bt;
	if (countOfMinus == 1)
	{
		for (int i = 0; output[i - 1] != '\0'; i++)
		{
			bt = output[i];
			output[i] = b;
			b = bt;
		}
	}

	return output;
}

//Функция, которая проверяет на наличе операций в выражении(необходимо для handler)
int checkOnOperations(char* input)
{
	for (int i = 0; input[i] != '\0'; i++)
	{
		if ((input[i] == '+') || input[i] == '*')
		{
			return 1;
		}
	}
	return 0;
}

//Функция, которая генерирует матрицу вида начало-конец скобок(необходимо для handler)
int** parenthesesArea(char* input)
{
	int count = 0;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == ')')
		{
			count++;
		}
	}

	int** mat = malloc(sizeof(int*) * count);
	for (int i = 0; i < count; i++)
	{
		mat[i] = malloc(sizeof(int) * 2);
	}

	for (int i = 0; i < count; i++)
	{
		mat[i] = malloc(sizeof(int) * 2);
	}
	int indOfStrFPair = 0;
	int indOfColFPair = 0;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '(')
		{
			int countOfCl = 0;
			int countOfOp = 0;
			for (int j = i; input[j] != '\0'; j++)
			{
				if (input[j] == '(')
				{
					countOfOp++;
				}
				if (input[j] == ')')
				{
					countOfCl++;
				}
				if ((input[j] == ')') && (countOfCl == countOfOp))
				{
					mat[indOfStrFPair][indOfColFPair++] = i;
					mat[indOfStrFPair++][indOfColFPair--] = j;
					break;
				}
			}
		}
	}

	return mat;
}

char* handler(char* input)
{
	while (checkOnOperations(input))
	{
		//Получаем скобки в выражении, для того, чтобы мы могли ставить преоритеты
		int** parentheses = parenthesesArea(input);
		int countOfParentheses = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if (input[i] == '(')
			{
				countOfParentheses++;
			}
		}

		int countOfOperations = 0;

		for (int i = 0; input[i] != '\0'; i++)
		{
			if ((input[i] == '+') || input[i] == '*')
			{
				countOfOperations++;
			}
		}

		int** priorityOfOperations = malloc(sizeof(int*) * countOfOperations);
		for (int i = 0; i < countOfOperations; i++)
		{
			priorityOfOperations[i] = malloc(sizeof(int) * 2);
			for (int j = 0; j < 2; j++)
			{
				priorityOfOperations[i][j] = 0;
			}
		}

		int indForArrayPrioryty = 0;
		for (int i = 0; input[i] != '\0'; i++)
		{
			if ((input[i] == '+') || (input[i] == '*'))
			{
				priorityOfOperations[indForArrayPrioryty][1] = i;
				if (input[i] == '+')
				{
					priorityOfOperations[indForArrayPrioryty][0]++;
				}
				if (input[i] == '*')
				{
					priorityOfOperations[indForArrayPrioryty][0]+=2;
				}

				for (int j = 0; j < countOfParentheses; j++)
				{
					if ((priorityOfOperations[indForArrayPrioryty][1] > parentheses[j][0]) && (priorityOfOperations[indForArrayPrioryty][1] < parentheses[j][1]))
					{
						priorityOfOperations[indForArrayPrioryty][0] += 2;
					}
				}
				indForArrayPrioryty++;
			}
		}

		//После нахождения операции с наивысшим преоритетом - генерируем мини-выражение и отправляем его в нужную функцию(sum/multip)
		int indOfMaxPriority = 0;
		int maxPriority = 0;
		for (int i = 0; i < countOfOperations; i++)
		{
			if (priorityOfOperations[i][0] > maxPriority)
			{
				maxPriority = priorityOfOperations[i][0];
				indOfMaxPriority = priorityOfOperations[i][1];
			}
		}

		int indOfStart = 0;
		int indOfEnd = 0;

		for (int i = (indOfMaxPriority - 1); i >= 0; i--)
		{
			if ((input[i] == '(') || (input[i] == ')') || (input[i] == '+') || (input[i] == '*'))
			{
				indOfStart = i+1;
				break;
			}
		}
		for (int i = (indOfMaxPriority + 1);; i++)
		{
			if ((input[i] == '(') || (input[i] == ')') || (input[i] == '+') || (input[i] == '*') || (input[i] == '\0'))
			{
				indOfEnd = i - 1;
				break;
			}
		}

		char* partOfCalculation = malloc(sizeof(char) * (indOfEnd-indOfStart+2));
		for (int i = 0; i <= (indOfEnd - indOfStart); i++)
		{
			partOfCalculation[i] = input[i + indOfStart];
		}
		partOfCalculation[indOfEnd - indOfStart + 1] = '\0';

		//Отправляем выражение в нужную функцию
		char* resOfPart = malloc(sizeof(char) * 2);
		resOfPart[0] = '-';
		resOfPart[1] = '\0';
		for (int i = 0; partOfCalculation[i] != '\0'; i++)
		{
			if (partOfCalculation[i] == '+')
			{
				free(resOfPart);
				resOfPart = operationOfSum(partOfCalculation);
				break;
			}
			if (partOfCalculation[i] == '*')
			{
				free(resOfPart);
				resOfPart = operationOfMultip(partOfCalculation);
				break;
			}
		}
		
		//Вносим результат промежуточных вычислений
		int lenOfPartRes = 0;
		for (int i = 0; resOfPart[i] != '\0'; i++)
		{
			input[indOfStart + i] = resOfPart[i];
			lenOfPartRes++;
		}

		//Смотрим, нужно ли удаляеть скобки, и если да-удаляем
		int parenthesesWasDel = 0;
		if ((input[indOfStart - 1] == '(') && (input[indOfEnd+1] == ')'))
		{
			for (int i = (indOfStart - 1); input[i-1] != '\0'; i++)
			{
				input[i] = input[i + 1];
			}
			parenthesesWasDel++;
		}
		if ((input[indOfEnd] == ')') && (parenthesesWasDel == 1))
		{
			for (int i = indOfEnd; input[i - 1] != '\0'; i++)
			{
				input[i] = input[i + 1];
			}
		}
		//Удаляем мусор после внесения результата промежуточного вычисления и печатаем новый вид выражения в консоль
		int varForMove = 0;
		for (int i = (indOfStart - parenthesesWasDel + lenOfPartRes); input[i - 1] != '\0'; i++)
		{
			input[i] = input[indOfEnd + 1 - parenthesesWasDel + (varForMove++)];
		}
		puts(input);

		//Чистим память
		for (int i = 0; i < countOfParentheses; i++)
		{
			free(parentheses[i]);
		}
		free(parentheses);
		for (int i = 0; i < countOfOperations; i++)
		{
			free(priorityOfOperations[i]);
		}
		free(priorityOfOperations);
		free(partOfCalculation);
		free(resOfPart);
	}
	return input;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	char input[1000];

	//Получаем выражение(в формате 100+-(100*-2))(т.е без пробелом, перед минусом указываем операцию которую программа исполняет с отрицательным числом)(нету деления)
	scanf("%s", &input);
	while ((getchar()) != '\n');

	//Запускаем функция коррекции выражения и выводим её результат
	findingErrors(&input[0]);
	puts(input);

	//Создаём строку - реузльтат
	char* res = handler(input);

	//Вывод результата
	puts(res);

	system("pause>nul");
	return 0;
}
