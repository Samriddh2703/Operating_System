/* Author: Samriddh Prasad */

#include<stdio.h>
#include<string.h>
#define MAX 100

struct Pros
{
    int pid, a_t, b_t,s_t,c_t,t_t,w_t,r_t;
};
int main()
{
    int n;
    struct Pros p[MAX];
    float avg_t_t, avg_w_t;
    int  total_t_t =0, total_w_t =0, total_r_t =0, total_i_t = 0, burst_rem[MAX], is_comp[MAX];
    memset(is_comp, 0, sizeof(is_comp));
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].a_t);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].b_t);
        p[i].pid = i + 1;
        burst_rem[i] = p[i].b_t;
        printf("\n");
    }
    int current_time, comp, prev = 0;
    while (comp != n)
    {
        int id = -1, m = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].a_t <= current_time && is_comp[i] == 0)
            {
                if (burst_rem[i] < m)
                {
                    m = burst_rem[i];
                    id = i;
                }
                if (burst_rem[i] == m)
                {
                    if (p[i].a_t < p[id].a_t)
                    {
                        m = burst_rem[i];
                        id = i;
                    }
                }
            }
        }

        if (id != -1)
        {
            if (burst_rem[id] == p[id].b_t)
            {
                p[id].s_t = current_time;
                total_i_t += p[id].s_t - prev;
            }
            burst_rem[id] -= 1;
            current_time++;
            prev = current_time;

            if (burst_rem[id] == 0)
            {
                p[id].c_t = current_time;
                p[id].t_t = p[id].c_t - p[id].a_t;
                p[id].w_t = p[id].t_t - p[id].b_t;
                p[id].r_t = p[id].s_t - p[id].a_t;

                total_t_t += p[id].t_t;
                total_w_t += p[id].w_t;
                total_r_t += p[id].r_t;

                is_comp[id] = 1;
                comp++;
            }
        }
        else
        {
            current_time++;
        }
    }
    avg_t_t = (float)total_t_t / n;
    avg_w_t = (float)total_w_t / n;

    printf("\n");

    printf("PId \t AT \t BT \t TAT \t WT \t RT  \n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d \t %d \t %d \t %d \t %d \t %d \n", p[i].pid, p[i].a_t, p[i].b_t, p[i].t_t, p[i].w_t, p[i].r_t);
    }

    printf("Average Turnaround Time = %.3f\n", avg_t_t);
    printf("Average Waiting Time = %.3f\n", avg_w_t);
}