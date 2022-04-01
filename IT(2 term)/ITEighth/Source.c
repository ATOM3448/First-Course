#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

struct order
{
	char payerAccount[21];
	char recipientAccount[21];
	int amount;

	short noNullFirst;
	short noNullSecond;
	short noNullThird;
};

int checkOnNums(char str[50])
{
	int flag = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] < '0') || (str[i] > '9'))
		{
			flag++;
			break;
		}
	}
	return flag;
}

void inputOfPayerAccount(int processedOrder, struct order* procOrder)
{
	char input[50];
	int out = 1;
	while (out)
	{
		system("cls");
		printf("Вы редактируете \"СЧЁТ ПЛАТЕЛЬЩИКА\" в ORDER #%d\n\nВвод: ", processedOrder);
		scanf("%s", &input);
		if (checkOnNums(input))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if ((strlen(input) > 20) || (strlen(input) < 20))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		strcpy(procOrder[0].payerAccount, input);
		procOrder[0].noNullFirst = 1;
		puts("Изменения внесены, для продолжения нажмите любую клавишу.");
		system("pause>nul");
		break;
	}
}

void inputOfRecipientAccount(int processedOrder, struct order* procOrder)
{
	char input[50];
	int out = 1;
	while (out)
	{
		system("cls");
		printf("Вы редактируете \"СЧЁТ ПОЛУЧАТЕЛЯ\" в ORDER #%d\n\nВвод: ", processedOrder);
		scanf("%s", &input);
		if (checkOnNums(input))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if ((strlen(input) > 20) || (strlen(input) < 20))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		strcpy(procOrder[0].recipientAccount, input);
		procOrder[0].noNullSecond = 1;
		puts("Изменения внесены, для продолжения нажмите любую клавишу.");
		system("pause>nul");
		break;
	}
}

void inputOfAmount(int processedOrder, struct order* procOrder)
{
	char input[50];
	int out = 1;
	while (out)
	{
		system("cls");
		printf("Вы редактируете \"СУММА\" в ORDER #%d\n\nВвод: ", processedOrder);
		scanf("%s", &input);
		if (checkOnNums(input))
		{
			puts("Сумма, предполагает собой набор из не более чем 9 и не менее чем 1 цифр.\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if ((strlen(input) > 9) || (strlen(input) < 1))
		{
			puts("Сумма, предполагает собой набор из не более чем 9 и не менее чем 1 цифр.\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		procOrder[0].amount = atoi(input);
		procOrder[0].noNullThird = 1;
		puts("Изменения внесены, для продолжения нажмите любую клавишу.");
		system("pause>nul");
		break;
	}
}

void editingMode(struct order* orders, int countOfOrders)
{
	system("cls");
	//Запрашиваем у пользователя какой ORDER он хочет редактировать
	char input[50];
	printf("Введите, какой ORDER вы хотите редактировать(1 - %d): ", countOfOrders);
	scanf("%s", &input);
	while ((getchar())!= '\n');
	if (checkOnNums(input))
	{
		puts("Аргументом является число!\nНажмите любую клавишу для повтора попытки!");
		system("pause>nul");
		return 0;
	}

	if ((atoi(input) < 1) || (atoi(input) > countOfOrders))
	{
		puts("Вы вышли за предел установленых значений!\nНажмите любую клавишу для повтора попытки!");
		system("pause>nul");
		return 0;
	}

	//Запрашиваем у пользователя, что он хочет отредактировать
	int processedOrder = atoi(input);
	int out = 1;
	while (out)
	{
		system("cls");
		printf("Вы редактируете ORDER #%d\nВыберите режим: \n\t1. Ввести счёт плательщика\n\t2. Ввести счёт получателя\n\t3. Ввести сумму\n\t4. Выйти из редактирования\nВвод: ", processedOrder);
		scanf("%s", &input);
		while ((getchar())!= '\n');

		if (checkOnNums(input))
		{
			puts("Аргументом является число!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if (strlen(input) > 1)
		{
			puts("Вы вышли за предел установленых значений!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		switch (input[0])
		{
		case '1':
			inputOfPayerAccount(processedOrder, &orders[processedOrder+1]);
			break;
		case '2':
			inputOfRecipientAccount(processedOrder, &orders[processedOrder+1]);
			break;
		case '3':
			inputOfAmount(processedOrder, &orders[processedOrder+1]);
			break;
		case '4':
			out = 0;
			printf("\nВы вышли из редактирования ORDER #%d!\nЧтобы продолжить нажмите любую клавишу!\n", processedOrder);
			system("pause>nul");
			break;
		default:
			puts("Вы вышли за предел установленых значений!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			break;
		}
	}
}

void viewingMode(struct order* orders, int countOfOrders)
{
	int out = 1;
	char input[50];
	while (out)
	{
		system("cls");
		puts("Введите ниже номер плательщика, информацию о снятой сумме которого вы хотите увидеть: ");
		scanf("%s", &input);
		if (checkOnNums(input))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if ((strlen(input) > 20) || (strlen(input) < 20))
		{
			puts("Номером счёта считается набор из 20 цифр, без пробелов\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		for (int i = 0; i < countOfOrders; i++)
		{
			if (!strcmp(input, orders[i].payerAccount))
			{
				if (orders[i].noNullThird)
				{
					printf("Результат запроса: %d\n", orders[i].amount);
				}
				else 
				{
					printf("Результат запроса: Информация не внесена\n");
				}
				printf("Для выхода из режима просмотра нажмите любую клавишу.");
				system("pause>nul");
				return 0;
			}
		}
		printf("Номер не найден. Попробуйте заного.");
		system("pause>nul");
		return 0;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");

	//Запрашиваем кол-во заказов
	int count;
	printf("Введите кол-во заказов: ");
	scanf("%d", &count);
	while ((getchar()) != '\n');

	//Создаём массив
	struct order* orders = malloc(sizeof(struct order) * count);
	for (int i = 0; i < count; i++)
	{
		orders[i].noNullFirst = 0;
		orders[i].noNullSecond = 0;
		orders[i].noNullThird = 0;
	}

	//Запрашиваем, что хочет сделать пользователь
	int out = 1;
	char input[50];
	while (out)
	{
		system("cls");
		printf("Выберите режим:\n\t1. Получить данные из ORDER\n\t2. Редактировать данные ORDER\n\t3. Выйти\nВвод: ");
		scanf("%s", input);
		while ((getchar())!= '\n');

		if (checkOnNums(input))
		{
			puts("Аргументом является число!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		if (strlen(input) > 1)
		{
			puts("Вы вышли за предел установленых значений!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			continue;
		}

		switch (input[0])
		{
		case '1':
			viewingMode(&orders[0], count);
			break;
		case '2':
			editingMode(&orders[0], count);
			break;
		case '3':
			out = 0;
			puts("Программа завершила своё выполнение!\nЧтобы продолжить нажмите любую клавишу!");
			system("pause>nul");
			break;
		default:
			puts("Вы вышли за предел установленых значений!\nНажмите любую клавишу для повтора попытки!");
			system("pause>nul");
			break;
		}
	}

	return 0;
}