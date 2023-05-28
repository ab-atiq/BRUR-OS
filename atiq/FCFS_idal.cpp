#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int at[], int wt[])
{
    int service_time[n];
    service_time[0] = 0;
    // service_time[0] = at[0]; // Service time for the first process is always 0

    // Calculate service time for each process
    for (int i = 1; i < n; i++)
    {
        // Service time = (time when the process completes its execution - arrival time)
        service_time[i] = bt[i - 1] + service_time[i - 1];

        // If the arrival time of the next process is after the service time, CPU idle occurs
        if (at[i] > service_time[i])
            service_time[i] = at[i];

        // Waiting time = (service time - arrival time)
        wt[i] = service_time[i] - at[i];
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
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
    }

    calculateAverageTime(n, burst_time, arrival_time); // Calculate average waiting time and average turnaround time

    return 0;
}
