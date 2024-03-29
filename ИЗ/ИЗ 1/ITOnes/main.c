#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int IsPrimeN(int num)
{
    //������� ���� ���������
        //������������ �������� ����� �����
        //�� ����� �������� �������� ����������� ��������� �� �����
    for (int i = 2; i <= (pow(num, 1 / 2) + 2); i++)
    {
        //���� ��� ������� �� ������ num �� i ��������� 0 - ���������� 0
        if ((num % i == 0) && (num != i))
        {
            return 0;
        }
    }
    //���� ��� ������� �� ������ num �� i �� ��������� 0 - ���������� 1
    return 1;
}

void IsPrime(int nums[], int countNums)
{
    //�������
    int count = 0; 

    //������� ������� �����
    for (int i = 0; i < countNums; i++)
    {
        if (IsPrimeN(nums[i]) == 1) 
        {
            count++;
        }
    }

    //�����
    printf("\n������� ����� � ������: %d\n", count);
}

int main(void)
{
    setlocale(LC_ALL, "rus");

    //��������� � �������� ���-�� ����������� �����, ���� ����� ����������� - ������������� ������
    int countNums;
    printf("������� ���-�� �����, ������� ����� ����������(�� ������ 1000 � �� ������ 1): ");
    scanf("%d", &countNums);
    if ((countNums > 1000) || (countNums < 1)) 
    {
        printf("������� ������������ ��������. ����������� 10");
        countNums = 10;
    }
    
    //��������� � �������� ������������ �����, ��� �� ����� �������� ��� ��������� �����, ���� ����� ����������� - ������������� ������
    int maxValue;
    printf("\n������� ����������� ���������� �����, ��� ��������� ��������������� �����, ������ ��� 1: ");
    scanf("%d", &maxValue);
    if (maxValue < 2)
    {
        printf("������� ������������ ��������. ����������� 10");
        maxValue = 10;
    }

    //������ ����������� ��������
    int nums[1000];

    //���������� �����
    for (int i = 0; i < countNums; i++)
    {
        nums[i] = 2 + rand()%(maxValue+1);
    }

    //�������� ������� �� ����� ���-�� ������� �����
    IsPrime(nums, countNums);

    return 0;
}