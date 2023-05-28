#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int pri[], int wt[])
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
    int highest = 0;  // Index of the process with the highest priority

    while (complete != n)
    {
        // Find the process with the highest priority among the arrived processes
        highest = -1;
        for (int i = 0; i < n; i++)
        {
            if (rt[i] > 0 && (highest == -1 || pri[i] < pri[highest]))
            {
                highest = i;
            }
        }

        // Update remaining time and waiting time for the selected process
        rt[highest]--;
        time++;

        // If the selected process is completed
        if (rt[highest] == 0)
        {
            complete++;
            wt[highest] = time - bt[highest];
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

void calculateAverageTime(int n, int bt[], int pri[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    calculateWaitingTime(n, bt, pri, wt);    // Calculate waiting time
    calculateTurnaroundTime(n, bt, wt, tat); // Calculate turnaround time

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], pri[i], wt[i], tat[i]);
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

    int burst_time[n]; // Burst time of each process
    int priority[n];   // Priority of each process

    printf("Enter burst time and priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
    }

    calculateAverageTime(n, burst_time, priority); // Calculate average waiting time and average turnaround time

    return 0;
}
