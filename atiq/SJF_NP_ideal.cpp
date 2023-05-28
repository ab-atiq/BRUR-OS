#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int at[], int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = 9999, shortest = 0, finish_time;
    int check = 0;

    // Check if all processes are completed
    while (complete != n)
    {
        // Find the process with the minimum remaining time among the arrived processes
        for (int j = 0; j < n; j++)
        {
            if (at[j] <= t && rt[j] < minm && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        // If no process is available at the current time, increment the time
        if (check == 0)
        {
            t++;
            continue;
        }

        // Update remaining time and minimum remaining time
        rt[shortest]--;
        minm = rt[shortest];

        // If the process is completed
        if (minm == 0)
        {
            minm = 9999;

            // Increment complete count
            complete++;

            // Calculate finish time
            finish_time = t + 1;

            // Calculate waiting time for the completed process
            wt[shortest] = finish_time - bt[shortest] - at[shortest];

            // If waiting time is negative, make it 0
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        // Increment time
        t++;
    }
}

void calculateTurnaroundTime(int n, int bt[], int wt[], int tat[])
{
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

void calculateAverageTime(int n, int bt[], int at[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    calculateWaitingTime(n, bt, at, wt);     // Calculate waiting time
    calculateTurnaroundTime(n, bt, wt, tat); // Calculate turnaround time

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f", avg_tat);
}

int main()
{
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];   // Burst time of each process
    int arrival_time[n]; // Arrival time of each process

    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
    }

    calculateAverageTime(n, burst_time, arrival_time); // Calculate average waiting time and average turnaround time

    return 0;
}