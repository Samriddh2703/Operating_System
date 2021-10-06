/* Author: Samriddh Prasad */

#include <stdio.h>
#define max 30

struct process
{
    int pid, at, bt, prior, st, ct, tat, wt, rt;
};

int main()
{

    int n;
    struct process p[max];
    float avgtat;
    float avgwt;
    int totaltat = 0,totalwt = 0,totalrt = 0,totalit=0;
    int burst_rem[max];
    int is_completed[max] = {0};
    printf("Enter no of process: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        printf("Enter priority of P%d: ", i + 1);
        scanf("%d", &p[i].prior);
        p[i].pid = i + 1;
        burst_rem[i] = p[i].bt;
        printf("\n");
    }

    int current_time =0 , completed = 0, prev = 0;

    while (completed != n)
    {
        int point = -1;
        int mx = 1000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && is_completed[i] == 0)
            {
                if (p[i].prior < mx)
                {
                    mx = p[i].prior;
                    point = i;
                }
                if (p[i].prior == mx)
                {
                    if (p[i].at < p[point].at)
                    {
                        mx = p[i].prior;
                        point = i;
                    }
                }
            }
        }

        if (point != -1)
        {
            if (burst_rem[point] == p[point].bt)
            {
                p[point].st = current_time;
                totalit += p[point].st - prev;
            }
            burst_rem[point] -= 1;
            current_time++;
            prev = current_time;

            if (burst_rem[point] == 0)
            {
                p[point].ct = current_time;
                p[point].tat = p[point].ct - p[point].at;
                p[point].wt= p[point].tat - p[point].bt;
                p[point].rt = p[point].st - p[point].at;

                totaltat += p[point].tat;
                totalwt += p[point].wt;
                totalrt += p[point].rt;

                is_completed[point] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    avgtat = (float)totaltat / n;
    avgwt = (float)totalwt / n;

    printf("\n");
    printf("PId\tAT\tBT\tPriority\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t   %d\t\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].prior, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turn Around Time = %.3f", avgtat);
    printf("\nAverage Waiting Time = %.3f", avgwt);
}
