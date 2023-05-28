#include <stdio.h>
#include <stdbool.h>

void calculateWaitingTime(int n, int bt[], int at[], int wt[])
{
    int rt[n]; // Remaining time

    // Initialize remaining time and waiting time arrays
    for (int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
        wt[i] = 0;
    }

    int complete = 0; // Number of completed processes
    int time = 0;     // Current time
    int shortest = 0; // Index of the process with the shortest remaining time

    while (complete != n)
    {
        // Find the process with the shortest remaining time among the arrived processes
        shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && (shortest == -1 || rt[i] < rt[shortest]))
            {
                shortest = i;
            }
        }

        // Update remaining time and waiting time for the selected process
        rt[shortest]--;
        time++;

        // If the selected process is completed
        if (rt[shortest] == 0)
        {
            complete++;
            wt[shortest] = time - at[shortest] - bt[shortest];
        }
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
