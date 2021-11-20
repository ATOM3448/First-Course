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
    printf("Печатается таблица функции, заданной рядом Тейлора\n");
    while(check == 1)
    {
        printf("Введите границы интервала\n\tЛевая: ");
        scanf("%lf", &A);
        printf("\tПравая: ");
        scanf("%lf", &B);
        if(A < B)
        {
            check = 0;
        }
        else
        {
            printf("Левая должна быть меньше правой! Повторите.\n");
        }
    }
    check = 1;
    printf("\nВведите шаг табулирования(Формат: 0,любое значение): ");
    scanf("%lf", &r);
        while(check == 1)
        {
            if(r < fabs(A - B))
            {
                check = 0;
            }
            else
            {
                printf("\n\tШаг должен быть меньше длинны интервала!\n\tПовторите: ");
                scanf("%lf", &r);
            }
        }
    printf("\nВведите допустимую погрешность вычисления(Формат: 0,любое значение):\n\t0 < eps <1: ");
    scanf("%lf", &eps);
    if((0 > eps) || (eps  > 1))
    {
        printf("\nВведено недопустимое значение. Положено eps = 0,00001");
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
