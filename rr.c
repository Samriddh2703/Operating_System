/* Author: Samriddh Prasad */

#include <stdio.h>
#include <unistd.h>

int n, tq, time = 0;
int queue[100] = {0}, f = 0, r = 0;
void sort();
void rr();
int select(int t);
void push(int q);
int pop();

struct data
{
    int at, bt1, bt, wt, tat;
} t;

int main()
{
    int i;
    float avg1 = 0, avg2 = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct data aa[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter Arrival time of process p%d:", i + 1);
        scanf("%d", &aa[i].at);
        printf("Enter Burst time of process p%d:", i + 1);
        scanf("%d", &aa[i].bt);
        aa[i].bt1 = aa[i].bt;
    }
    printf("Enter time_quantum: ");
    scanf("%d", &tq);
    sort(aa);
    rr(aa);

    printf("\nPID\tAT\tBT\tTAT\tWT");
    for (i = 0; i < n; i++)
    {
        printf("\np%d\t%d\t%d\t%d\t%d", i + 1, aa[i].at, aa[i].bt1, aa[i].tat, aa[i].wt);
        avg1 += aa[i].wt;
        avg2 += aa[i].tat;
    }
    printf("\n");
    printf("\nAverage Turn Around Time : %.3f", avg2 / n);
    printf("\nAverage wait time : %.3f", avg1 / n);

    return 0;
}


void sort(struct data a[])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j].at > a[j + 1].at)
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

void rr(struct data a[])
{
    int i = 1, j = 0, x;
    x = n;
    while (x != 0)
    {
        j = select(j);
        if (a[j].bt <= tq && a[j].bt > 0)
        {
            time = time + a[j].bt;
            a[j].bt = 0;
        }
        else if (a[j].bt > 0)
        {
            a[j].bt = a[j].bt - tq;
            time = time + tq;
        }
        while (a[i].at <= time && i < n)
        {
            push(i);
            i++;
        }
        if (a[j].bt == 0)
        {
            x--;
            a[j].wt = time - a[j].at - a[j].bt1;
            a[j].tat = a[j].wt + a[j].bt1;
        }
        else
        {
            push(j);
        }
    }
}

int select(int j)
{
    if (time == 0)
    {
        return j;
    }
    else
    {
        j = pop();
        return j;
    }
}

int pop()
{
    int x;
    x = queue[f++];
    return x;
}

void push(int q)
{
    queue[r++] = q;
}