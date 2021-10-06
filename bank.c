/* Author: Samriddh Prasad */

#include <stdio.h>
#include <stdlib.h>

void display(int arr[][20], int n, int p)
{
    int l, t;
    for (l = 0; l < n; l++)
    {
        printf("\n");
        for (t = 0; t < p; t++)
        {
            printf("%d\t", arr[l][t]);
        }
    }
     printf("\n");
}

void Banker(int A[][20], int N[][20],int M[20][20], int W[1][20], int *n, int *m)
{
    int l, t;
    printf("\nEnter number of processes(n) : ");
    scanf("%d", n);
    printf("\nEnter number of resource types(m) : ");
    scanf("%d", m);

    printf("\nEnter the Current Allocation Matrix\n");
    for (l = 0;  l< *n; l++)
    {
        for (t = 0; t < *m; t++)
        {
            scanf("%d", &A[l][t]);
        }
    }

    printf("\nEnter the Maximum Need Matrix\n");
    for (l = 0; l < *n; l++)
    {
        for (t = 0; t < *m; t++)
        {
            scanf("%d", &M[l][t]);
        }
    }

    printf("\nCurrently available resource for : \n");
    for (l = 0; l < *m; l++)
    {
        printf(" R%d : ", l + 1);
        scanf("%d", &W[0][l]);
    }

    for (l = 0; l < *n; l++)
        for (t = 0; t < *m; t++)
            N[l][t] = M[l][t] - A[l][t];

    printf("\nAllocation Matrix is:\n");
    display(A, *n, *m);
    printf("\nMaximum Need Matrix is:\n");
    display(M, *n, *m);
    printf("\nRemaining Need Matrix is:\n");
    display(N, *n, *m);
}


int safety(int A[][20], int N[][20],int B[1][20], int n, int m, int a[])
{
    int l, t, k, x = 0, f1 = 0, f2 = 0;
    int F[20], W[1][20];
    for (l = 0; l < n; l++)
        F[l] = 0;
    for (l = 0; l < m; l++)
        W[0][l] = B[0][l];

    for (t = 0; t < n; t++)
    {
        for (l = 0; l < n; l++)
        {
            if (F[l] == 0)
            {
                f2 = 0;
                for (t = 0; t < m; t++)
                {
                    if (N[l][t] > W[0][t])
                        f2 = 1;
                }
                if (f2 == 0 && F[l] == 0)
                {
                    for (t = 0; t < m; t++)
                        W[0][t] += A[l][t];
                    F[l] = 1;
                    f1++;
                    a[x++] = l;
                }
            }
        }
        if (f1 == n)
            return 1;
    }
    return 0;
}



void request(int A[20][20], int N[20][20], int B[20][20], int pid, int K)
{
    int rmat[1][20];
    int l;
    printf("\n Enter request : \n");
    for (l = 0; l < K; l++)
    {
        printf(" For R%d : ", l + 1);
        scanf("%d", &rmat[0][l]);
    }

    for (l = 0; l < K; l++)
        if (rmat[0][l] > N[pid][l])
        {
            printf("\n Error occurred\n");
            exit(0);
        }

    for (l = 0; l < K; l++)
        if (rmat[0][l] > B[0][l])
        {
            printf("\n Resources are not available\n");
            exit(0);
        }

    for (l = 0; l < K; l++)
    {
        B[0][l] -= rmat[0][l];
        A[pid][l] += rmat[0][l];
        N[pid][l] -= rmat[0][l];
    }
}


int banker(int A[][20], int N[][20],int W[1][20], int n, int m)
{
    int l,t, a[20];
    t = safety(A, N, W, n, m, a);
    if (t != 0)
    {
        printf("\n It is a safe sequence \n");
        for (l = 0; l < n-1; l++)
            printf(" P%d -> ", a[l]);
            printf(" P%d ",a[n-1]);
        printf("\n");
        return 1;
    }
    else
    {
        printf("\n Deadlock has occured\n");
        return 0;
    }
}




int main()
{
    int All[20][20], Max[20][20], Need[20][20], W[1][20];
    int n, m, pid, c, r;
 
    Banker(All, Need, Max, W, &n, &m);
    r = banker(All, Need, W, n, m);
    if (r != 0)
    {
        printf("\n Do you want make a new request for any process? (1=Yes|0=No): ");
        scanf("%d", &c);
        if (c == 1)
        {
            printf("\n Enter process number for new request : ");
            scanf("%d", &pid);
            request(All, Need, W, pid , m);
            r = banker(All, Need, W, n, m);
            if (r == 0)
            {
                exit(0);
            }
        }
    }
    else
        exit(0);
    return 0;
}
