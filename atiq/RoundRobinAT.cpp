#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int wt[], int quantum, int at[])
{
    int remaining_time[n];

    // Initialize remaining time array
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = bt[i];
    }

    int complete = 0; // Number of completed processes
    int time = 0;     // Current time

    while (complete != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0 && at[i] <= time)
            {
                // Execute a quantum of the process
                if (remaining_time[i] > quantum)
                {
                    time += quantum;
                    remaining_time[i] -= quantum;
                }
                else
                {
                    // Execute the remaining burst time of the process
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    complete++;

                    // Calculate the waiting time for the completed process
                    wt[i] = time - bt[i] - at[i];
                }
            }
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

void calculateAverageTime(int n, int bt[], int quantum, int at[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    calculateWaitingTime(n, bt, wt, quantum, at); // Calculate waiting time
    calculateTurnaroundTime(n, bt, wt, tat);      // Calculate turnaround time

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

    int quantum; // Time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    calculateAverageTime(n, burst_time, quantum, arrival_time); // Calculate average waiting time and average turnaround
}