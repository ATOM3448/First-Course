#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void addOneEliment(int masLen, int mas[])
{
    int indexOfEndSeries = 0;
    int lenOfMaxSeries = 0;
    int lenOfSeries = 1;
    int buferOne;
    int buferTo;

    //Перебераем все эллементы массива, если число в индексе эквивалентно числу, в индексе+1,
    //увеличиваем длинну серии, если серия прерывается, проверяем, больше ли она прошлой максимальной
    //если да - обновляем максимальную серию и записываем индекс конца серии
    for (int index = 0; index < masLen; index++)
    {
        if (mas[index] == mas[index + 1])
        {
            lenOfSeries++;
        }
        else
        {
            lenOfSeries = 1;
        }
        if (lenOfMaxSeries <= lenOfSeries)
        {
            lenOfMaxSeries = lenOfSeries;

            //Сохраняем число, серию которого увеличиваем на 1
            buferTo = mas[index]; 

            if (lenOfMaxSeries > 1)
            {
                indexOfEndSeries = index + 1;
            }
            else
            {
                indexOfEndSeries = index;
            }
        }
    }

    //Переписываем значения в массиве
    for (int index = indexOfEndSeries; index <= masLen; index++)
    {
        //Сохраняем текущее значение
        buferOne = mas[index]; 
        //Заносим новое значение
        mas[index] = buferTo;
        //Устанавливаем число, которое нужно будет внести в следующий элемент массива
        buferTo = buferOne;
    }

    //Вывод конечного массива
    for (int index = 0; index <= masLen; index++)
    {
        printf("%d ", mas[index]);
    }
}

int main(void)
{
    setlocale(LC_ALL, "rus");

    //Получаем максимальный размер массива
    int masLen;
    printf("Введите максимальный размер массива (Больше 0 и меньше 1000)");
    scanf("%d", &masLen);
    if ((masLen < 1) || (masLen > 999))
    {
        printf("Введенно некорректное число. Установлено 10");
        masLen = 10;
    }

    //Получаем максимально возможное сгенерированное число
    int max;
    printf("\nВведите максимально возможное сгенерированное число (Больше 0)");
    scanf("%d", &max);
    if (max < 1)
    {
        printf("Введенно некорректное число. Установлено 10");
        max = 10;
    }
    printf("\n");

    //Генерируем и выводим массив
    int mas[1001];
    for (int index = 0; index < masLen; index++)
    {
        mas[index] = rand()%(max+1);
        printf("%d ", mas[index]);
    }

    printf("\n");

    addOneEliment(masLen, &mas[0]);

    return 0;
}