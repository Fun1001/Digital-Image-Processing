#include<stdio.h>
int main()
{
    int i = 0;
    int j = 0;
    int t = 1;

    for (i = 2; i <= 100; i++)
    {
        for (j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                t = 0;
                break;
            }
        }
        if (t == 1)
        {
            printf("%d\n", i);
        }
        t = 1;
    }
    return 0;
}