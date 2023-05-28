#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int wt[], int at[])
{
    int complete[n];   // To keep track of completed processes
    int remaining = n; // Number of remaining processes

    int shortest = 0; // Index of the process with the shortest burst time

    int time = 0; // Current time

    // Initialize the complete array as false
    for (int i = 0; i < n; i++)
        complete[i] = 0;

    while (remaining != 0)
    {
        // Find the process with the shortest burst time among the arrived processes
        shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (complete[i] == 0 && at[i] <= time)
            {
                if (shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if (shortest == -1)
        {
            // If no process is available at the current time, increment the time
            time++;
        }
        else
        {
            // Calculate the waiting time for the selected process
            wt[shortest] = time - at[shortest];

            // Update the current time and mark the process as complete
            time += bt[shortest];
            complete[shortest] = 1;
            remaining--;
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

    calculateWaitingTime(n, bt, wt, at);     // Calculate waiting time
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

    calculateAverageTime(n, burst_time, arrival_time); // Calculate average
    return 0;
}
