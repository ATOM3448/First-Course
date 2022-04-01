#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void findingErrors(char* input)
{
	//Все проверки делаем 3 раза, бывают ситуации когда по одной не хватает 
	for (int hgh = 0; hgh < 3; hgh++)
	{
		//Проверка на лишние символы
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

		//Проверка на повторы
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

		//Проверка на лишние скобки
		//Подсчитаем сколько открывающих и закрывающих
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

		//Создадим массив, где будем хранить пары индексов op|cl, память выделим по количетсву удобного для нас символа - '(', это допустимо т.к лишние символы мы будем удалять, а если встретятся ')' без открытия, то они являются лишними, ну а если будет большей открытий, мы запишем в лишние те - что без пары
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

		//Удалим из массива ячейки без данных
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

		//Чистим все лишние скобки(те, что не в массиве)
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


		//Проверка на лишние(бесмысленный знак в начале, бесмысленный знак в конце, знак справа от открывающей скобки, знак слева от закрывающей скобки)
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

		//Чистим пустые пары скобок
		//Снова определяем пары(прошлые данные не используем т.к выражение уже потерпело множество изменений и старые индексы не актуальны, а порядок определения ошибок изменять нельзя)
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
		
		//Чистим пары скобок, внутри которых отсутсвуют операторы +/*
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

		//Проверка на наличе знака '*' перед||после '-' || '(' || ')', если нету других
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
	//Разделим выражение на 2 части, где чать - число
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

	//Выделяем память под ответ(он не может быть больше, чем длина всего выражения) 
	char* output = malloc(sizeof(char) * sizeOfString + 1);
	output[sizeOfString] = '\0';
	//Заполним строку вывода спец. символами для лёгкой обработки в дальнейшем
	for (int i = 0; i < sizeOfString; i++)
	{
		output[i] = '?';
	}

	//Возвращаемся к разделению строки на числа 
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

	//Ставим режим суммирования: 0 - только положительные числа; 1 - одно из чисел отрицательно; 2 - оба числа отрицательые
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

	//Складываем
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
		//Блок всяческих проверок
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

		//Блок вычислений
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

		//Блок отрицания и принятия
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

	//Убираем спец. символы и лишние нули
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

	//Делаем обязательные перед выходом из функции вещи и выходим
	free(nums[1]);
	free(nums[0]);
	free(nums);
	return output;
}

char* operationOfMultip(char* input)
{
	//Удалим "Минус" из выражения
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

	//Разделим выражение на 2 части, где чать - число
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

	//Возвращаемся к разделению строки на числа 
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

	//Чистим лишние нули
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

	//Ищем наибольшее(по длине) число для оптимизации блока произведения
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

	//Выполняем произведение
	//Создадим поля для результатов призведения числа на ЦИФРУ
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

	//Выполняем произведение числа на ЦИФРЫ
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
	//Складываем наши результаты для получения конечного результата
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

	//Делаем обязательные перед выходом из функции вещи и выходим
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

//Функция для handler
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

//Функция для handler
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
		//Распределяем уровни приоритета
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

		//Определяем "Область действия" оператора с наивысшим преоритетом(первым оператором с наивысшим приортетом)
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

		//Вычисляем часть с наивысшим приоритетом
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
		
		//Вставляем результат части в общее выражение, на место части выражения
		int lenOfPartRes = 0;
		for (int i = 0; resOfPart[i] != '\0'; i++)
		{
			input[indOfStart + i] = resOfPart[i];
			lenOfPartRes++;
		}

		//Чистим скобки(если они были)
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
		//Заполним пространство, которое не заменилось при вставке
		int varForMove = 0;
		for (int i = (indOfStart - parenthesesWasDel + lenOfPartRes); input[i - 1] != '\0'; i++)
		{
			input[i] = input[indOfEnd + 1 - parenthesesWasDel + (varForMove++)];
		}
		puts(input);

		//Очистка памяти
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

	//Запрашиваем у пользователя строку - выражение
	scanf("%s", &input);
	while ((getchar()) != '\n');

	//Вызываем функцию обработки выражения
	findingErrors(&input[0]);
	puts(input);

	//Вызываем функцию счёта
	char* res = handler(input);

	//Вывод
	puts(res);

	system("pause>nul");
	return 0;
}

/*
* Идеи оптимизации:
*	- Сделать отдельную функцию для удаления символа, а не каждый раз писать код по новой
*	- Сделать функцию делящую числа для операции отдельно, а не свою в каждой функции операции
*	- Вместо двух отедльных переменных чисел в строке, сделать структуру, где будут параметры числа(Отрицательное/положительное)
*/

/*
* Подсказочки:
* Значение чар при '0' - 48
*/