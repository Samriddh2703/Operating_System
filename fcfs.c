/* Author: Samriddh Prasad */

#include<stdio.h>
#include<unistd.h>
#define MAX 30
struct process
{
    int bt, at, ct, wt, tat;
} pro[MAX], temp[MAX];

int main()
{
    int npro, i, j, y;
    float avgwt = 0, avgtat = 0;
    printf("Enter No Of Process:");
    scanf("%d", &npro);
    for (i = 0; i < npro; i++)
    {
        printf("Arrival Time of Process %d: ", i + 1);
        scanf("%d", &pro[i].at);

        printf("Burst Time of Process %d: ", i + 1);
        scanf("%d", &pro[i].bt);
    }
    for (i = 0; i < npro; i++)
    {
        for (j = i + 1; j < npro; j++)
        {
            if (pro[i].at > pro[j].at)
            {
                temp[i] = pro[i];
                pro[i] = pro[j];
                pro[j] = temp[i];
            }
        }
    }
    pro[0].ct = pro[0].bt + pro[0].at;
    for (i = 1; i < npro; i++)
    {
        if (pro[i - 1].ct < pro[i].at)
            pro[i].ct = pro[i].at + pro[i].bt;
        else
            pro[i].ct = pro[i - 1].ct + pro[i].bt;
    }
    for (i = 0; i < npro; i++)
    {
        pro[i].tat = pro[i].ct - pro[i].at;
        avgtat += pro[i].tat;
    }
    pro[0].wt = 0;
    avgwt += pro[0].wt;
    for (i = 1; i < npro; i++)
    {
        pro[i].wt = pro[i].tat - pro[i].bt;
        avgwt += pro[i].wt;
    }
    printf("\n");
    printf("PId\t AT\t BT\t TAT\t WT\n");
    for (i = 0; i < npro; i++)
        printf("P%d\t %d\t %d\t %d\t %d\n", i + 1, pro[i].at, pro[i].bt, pro[i].tat, pro[i].wt);

    printf("\nAverage Turn Around Time = %.3f", avgtat / npro);
    printf("\nAverage Waiting Time = %.3f", avgwt / npro);
}