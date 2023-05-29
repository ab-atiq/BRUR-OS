// only for sir code
#include <stdio.h>
#include <conio.h>
#include <string.h>
int main()
{
    int et[20], at[10], n, i, j, temp, st[10], ft[10], wt[10], ta[10];
    int totwt = 0, totta = 0;
    float awt, ata;
    char pn[10][10], t[10];
    // clrscr();
    printf("Enter the number of process:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter process name, arrival time & execution time:");
        // flushall();
        scanf("%s%d%d", pn[i], &at[i], &et[i]);
    }
    // sort
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (et[i] < et[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = et[i];
                et[i] = et[j];
                et[j] = temp;

                strcpy(t, pn[i]);
                strcpy(pn[i], pn[j]);
                strcpy(pn[j], t);
            }
        }
    for (i = 0; i < n; i++)
    {
        if (i == 0)
            st[i] = at[i];
        else
            st[i] = ft[i - 1];
        wt[i] = st[i] - at[i];
        ft[i] = st[i] + et[i];
        ta[i] = ft[i] - at[i];
        totwt += wt[i];
        totta += ta[i];
    }
    awt = (float)totwt / n;
    ata = (float)totta / n;
    printf("\nPname\tarrivaltime\texecutiontime\twaitingtime\ttatime");
    for (i = 0; i < n; i++)
        printf("\n%s\t%5d\t\t%5d\t\t%5d\t\t%5d", pn[i], at[i], et[i], wt[i], ta[i]);
    printf("\nAverage waiting time is:%f", awt);
    printf("\nAverage turnaroundtime is:%f", ata);
    getch();
    return 0;
}
/*
Enter the number of process:3
Enter process name, arrival time & execution time:p1 4 6
Enter process name, arrival time & execution time:p2 5 15
Enter process name, arrival time & execution time:p3 6 11

Pname   arrivaltime     executiontime   waitingtime     tatime
p1          4               6               0               6
p3          6              11               4              15
p2          5              15              16              31
Average waiting time is:6.666667
Average turnaroundtime is:17.333334
*/