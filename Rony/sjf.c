
// shortest job first algorithm
// only apply when CPU  is not idal

#include <stdio.h>
int main(int argc, char const *argv[])
{

    int i, j, index, tt = 0, sum = 0, Total_TAT = 0, Total_WT = 0;
    int PN[10] = {0}, AT[10] = {0}, BT[10] = {0}, CT[10] = {0}, TAT[10] = {0}, WT[10] = {0}, temp;
    int N;
    printf("Enter the number of Process = ");
    scanf("%d", &N);
    printf("Enter process sequence = ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &PN[i]);
    }

    printf("Enter Arrival time = ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &AT[i]);
    }

    printf("Enter Burst time = ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &BT[i]);
    }

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (BT[i] > BT[j])
            {
                temp = PN[i];
                PN[i] = PN[j]; // short process sequence time
                PN[j] = temp;

                temp = AT[i];
                AT[i] = AT[j]; // short arival time
                AT[j] = temp;

                temp = BT[i];
                BT[i] = BT[j]; // short burst time
                BT[j] = temp;
            }
        }
    }

    int min = AT[0];
    for (i = 0; i < N; i++)
    {
        if (min > AT[i])
        {
            min = AT[i];
            index = i;
        }
    }
    tt = min;
    CT[index] = BT[index] + tt;
    tt = CT[index];

    for (i = 0; i < N; i++)
    {

        if (AT[i] != min)
        {
            CT[i] = BT[i] + tt;
            tt = CT[i];
        }
    }
    printf("\n\n\tSolution For SJF  CPU Schedulling\n");
    printf("Process\t AT \t BT\tTAT \t WT  \n");
    for (i = 0; i < N; i++)
    {
        TAT[i] = CT[i] - AT[i];
        Total_TAT = Total_TAT + TAT[i];
        WT[i] = TAT[i] - BT[i];
        Total_WT = Total_WT + WT[i];
        printf("P%d \t %d \t %d \t %d \t %d\n", PN[i], AT[i], BT[i], TAT[i], WT[i]);
    }

    float Average_TAT = Total_TAT / (float)N;
    float Average_WT = Total_WT / (float)N;

    printf("Average waiting time = %.3f\n", Average_WT);
    printf("Average Turnaround time = %.3f\n", Average_TAT);

    return 0;
}
