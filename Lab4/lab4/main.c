#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

double series(double, double);

int main()
{
    setlocale(LC_ALL, "rus");
    double A, B, r, eps, x, Fx;
    int check = 1;
    printf("���������� ������� �������, �������� ����� �������\n");
    while(check == 1)
    {
        printf("������� ������� ���������\n\t�����: ");
        scanf("%lf", &A);
        printf("\t������: ");
        scanf("%lf", &B);
        if(A < B)
        {
            check = 0;
        }
        else
        {
            printf("����� ������ ���� ������ ������! ���������.\n");
        }
    }
    check = 1;
    printf("\n������� ��� �������������(������: 0,����� ��������): ");
    scanf("%lf", &r);
        while(check == 1)
        {
            if(r < fabs(A - B))
            {
                check = 0;
            }
            else
            {
                printf("\n\t��� ������ ���� ������ ������ ���������!\n\t���������: ");
                scanf("%lf", &r);
            }
        }
    printf("\n������� ���������� ����������� ����������(������: 0,����� ��������):\n\t0 < eps <1: ");
    scanf("%lf", &eps);
    if((0 > eps) || (eps  > 1))
    {
        printf("\n������� ������������ ��������. �������� eps = 0,00001");
        eps = 0.00001f;
    }

    printf("\n+---------------+\n");
    printf("|   X   |  F(x) |\n");

    while(A <= B)
    {
        x = A;
        Fx = series(x, eps);
        if(Fx == 0)
        {
            A += r;
            continue;
        }
        printf("--------+--------\n");
        printf("|%7.2lf|%7.2lf|\n", x, Fx);
        printf("+---------------+\n");

        A += r;
    }

    getchar();
    return 0;
}
