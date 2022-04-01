#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

void findingErrors(char* input)
{
	//��� �������� ������ 3 ����, ������ �������� ����� �� ����� �� ������� 
	for (int hgh = 0; hgh < 3; hgh++)
	{
		//�������� �� ������ �������
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

		//�������� �� �������
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

		//�������� �� ������ ������
		//���������� ������� ����������� � �����������
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

		//�������� ������, ��� ����� ������� ���� �������� op|cl, ������ ������� �� ���������� �������� ��� ��� ������� - '(', ��� ��������� �.� ������ ������� �� ����� �������, � ���� ���������� ')' ��� ��������, �� ��� �������� �������, �� � ���� ����� ������� ��������, �� ������� � ������ �� - ��� ��� ����
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

		//������ �� ������� ������ ��� ������
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

		//������ ��� ������ ������(��, ��� �� � �������)
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


		//�������� �� ������(������������ ���� � ������, ������������ ���� � �����, ���� ������ �� ����������� ������, ���� ����� �� ����������� ������)
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

		//������ ������ ���� ������
		//����� ���������� ����(������� ������ �� ���������� �.� ��������� ��� ��������� ��������� ��������� � ������ ������� �� ���������, � ������� ����������� ������ �������� ������)
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
		
		//������ ���� ������, ������ ������� ���������� ��������� +/*
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

		//�������� �� ������ ����� '*' �����||����� '-' || '(' || ')', ���� ���� ������
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
	//�������� ��������� �� 2 �����, ��� ���� - �����
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

	//�������� ������ ��� �����(�� �� ����� ���� ������, ��� ����� ����� ���������) 
	char* output = malloc(sizeof(char) * sizeOfString + 1);
	output[sizeOfString] = '\0';
	//�������� ������ ������ ����. ��������� ��� ����� ��������� � ����������
	for (int i = 0; i < sizeOfString; i++)
	{
		output[i] = '?';
	}

	//������������ � ���������� ������ �� ����� 
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

	//������ ����� ������������: 0 - ������ ������������� �����; 1 - ���� �� ����� ������������; 2 - ��� ����� ������������
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

	//����������
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
		//���� ��������� ��������
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

		//���� ����������
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

		//���� ��������� � ��������
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

	//������� ����. ������� � ������ ����
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

	//������ ������������ ����� ������� �� ������� ���� � �������
	free(nums[1]);
	free(nums[0]);
	free(nums);
	return output;
}

char* operationOfMultip(char* input)
{
	//������ "�����" �� ���������
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

	//�������� ��������� �� 2 �����, ��� ���� - �����
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

	//������������ � ���������� ������ �� ����� 
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

	//������ ������ ����
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

	//���� ����������(�� �����) ����� ��� ����������� ����� ������������
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

	//��������� ������������
	//�������� ���� ��� ����������� ����������� ����� �� �����
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

	//��������� ������������ ����� �� �����
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
	//���������� ���� ���������� ��� ��������� ��������� ����������
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

	//������ ������������ ����� ������� �� ������� ���� � �������
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

//������� ��� handler
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

//������� ��� handler
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
		//������������ ������ ����������
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

		//���������� "������� ��������" ��������� � ��������� �����������(������ ���������� � ��������� ����������)
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

		//��������� ����� � ��������� �����������
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
		
		//��������� ��������� ����� � ����� ���������, �� ����� ����� ���������
		int lenOfPartRes = 0;
		for (int i = 0; resOfPart[i] != '\0'; i++)
		{
			input[indOfStart + i] = resOfPart[i];
			lenOfPartRes++;
		}

		//������ ������(���� ��� ����)
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
		//�������� ������������, ������� �� ���������� ��� �������
		int varForMove = 0;
		for (int i = (indOfStart - parenthesesWasDel + lenOfPartRes); input[i - 1] != '\0'; i++)
		{
			input[i] = input[indOfEnd + 1 - parenthesesWasDel + (varForMove++)];
		}
		puts(input);

		//������� ������
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

	//����������� � ������������ ������ - ���������
	scanf("%s", &input);
	while ((getchar()) != '\n');

	//�������� ������� ��������� ���������
	findingErrors(&input[0]);
	puts(input);

	//�������� ������� �����
	char* res = handler(input);

	//�����
	puts(res);

	system("pause>nul");
	return 0;
}

/*
* ���� �����������:
*	- ������� ��������� ������� ��� �������� �������, � �� ������ ��� ������ ��� �� �����
*	- ������� ������� ������� ����� ��� �������� ��������, � �� ���� � ������ ������� ��������
*	- ������ ���� ��������� ���������� ����� � ������, ������� ���������, ��� ����� ��������� �����(�������������/�������������)
*/

/*
* �����������:
* �������� ��� ��� '0' - 48
*/