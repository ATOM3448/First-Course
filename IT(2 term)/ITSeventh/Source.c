#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct 
{
	char name[50];
	char secondName[50];
	char group[6];
	char** subject;
	int* mark;
}studentAcademicPerformance;

studentAcademicPerformance createNewStudent(char name[50], char secondName[50], char group[6], int defMarks)
{
	//Создаём экземпляр
	studentAcademicPerformance student;

	//Заносим имя
	strcpy(student.name, name);
	
	//Заносим фамилию
	strcpy(student.secondName, secondName);

	//Заносим группу
	strcpy(student.group, group);

	//Создаём в карточке предметы
	student.subject = malloc(sizeof(char*) * 6);
	for (int i = 0; i < 6; i++)
	{
		student.subject[i] = malloc(sizeof(char) * 10);
	}
	student.subject[0] = "Prog";
	student.subject[1] = "Math";
	student.subject[2] = "Info";
	student.subject[3] = "Engl";
	student.subject[4] = "Rus";
	student.subject[5] = "MatAnl";

	//Создаём поле оценок
	student.mark = malloc(sizeof(int) * 6);

	//Заносим дефолтные значения в поле оценок
	for (int i = 0; i < 6; i++)
	{
		student.mark[i] = defMarks;
	}

	//Возвращаем экземпляр
	return student;
}

void objOut(studentAcademicPerformance student)
{
	printf("____________\n%s %s | %s\n------------\n", student.secondName, student.name, student.group);
	for (int i = 0; i < 6; i++)
	{
		printf("%s | %d\n------------\n", student.subject[i], student.mark[i]);
	}
	printf("\n\n\n");
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");

	//Создадим массивы с фамилиями и группами
	char names[10][50] = { {"Александр"}, {"Владислав"}, {"Даниил"}, {"Вячеслав"}, {"Владимир"}, {"Никита"}, {"Роман"}, {"Антон"}, {"Глеб"}, {"Алик"} };
	char secondNames[10][50] = { {"Иванов"}, {"Петров"}, {"Сидоров"}, {"Августинский"}, {"Добролюбов"}, {"Смирнов"}, {"Шестаков"}, {"Простаков"}, {"Алексеев"}, {"Боженов"} };
	char groups[10][6] = { {"431-3"}, {"431-2"}, {"431-1"}, {"441-1"}, {"441-2"}, {"341-3"}, {"532-3"}, {"143-3"}, {"214-2"}, {"411-3"} };

	//Спрашиваем, сколько сгенерировать
	int count;
	printf("Сколько карточек сгенерировать: ");
	scanf("%d", &count);

	//Генерируем
	studentAcademicPerformance* students = malloc(sizeof(studentAcademicPerformance) * count);
	for (int i = 0; i < count; i++)
	{
		students[i] = createNewStudent(names[rand()%10], secondNames[rand()%10], groups[rand()%10], 4);
		
		//Сгенерируем случайные оценки
		for (int j = 0; j < 6; j++)
		{
			students[i].mark[0] = 3 + rand() % 3;
			students[i].mark[1] = 3 + rand() % 3;
			students[i].mark[2] = 3 + rand() % 3;
			students[i].mark[3] = 3 + rand() % 3;
			students[i].mark[4] = 3 + rand() % 3;
			students[i].mark[5] = 3 + rand() % 3;
		}
	}

	//Выведем получившиеся карточки
	for (int i = 0; i < count; i++)
	{
		objOut(students[i]);
	}

	//Выведем тех, у кого оценки только > 3
	printf("Хорошисты и отличники:\n");
	for (int i = 0; i < count; i++)
	{
		int flag = 1;
		for (int j = 0; j < 6; j++)
		{
			if (students[i].mark[j] < 4)
			{
				flag--;
				break;
			}
		}
		if (flag)
		{
			printf("%s %s\n", students[i].secondName, students[i].name);
		}
	}

	getch();
	return 0;
}