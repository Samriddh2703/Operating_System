/* Author: Samriddh Prasad */

#include <stdio.h>

int main()
{
    struct Process
    {
        int pid, bt, art;
    } proc[20];
    int n, i;

    printf("Enter no of process: ");
    scanf("%d", &n);
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    int rt[n];

    for (i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;

        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &proc[i].art);

        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

    {
        for (int i = 0; i < n; i++)
            tat[i] = proc[i].bt + wt[i];
    }

    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = 10000000;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {

        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = 10000000;

        if (rt[shortest] == 0)
        {

            complete++;
            check = 0;

            finish_time = t + 1;
            wt[shortest] = finish_time -
                           proc[shortest].bt -
                           proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }

    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];

    printf("PId\t AT\t BT\t TAT\t WT\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("P%d\t %d\t %d\t %d\t %d\t\n", proc[i].pid, proc[i].art, proc[i].bt, tat[i], wt[i]);
    }

    printf("\nAverage Turn Around Time = %.3f", (float)total_tat / (float)n);
    printf("\nAverage Waiting Time = %.3f", (float)total_wt / (float)n);
}
