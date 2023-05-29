// all okey
#include <stdio.h>

int calculate_waiting_times(int pid[], int arrival_time[], int burst_time[], int waiting_time[], int n)
{
    int total_waiting_time = 0;
    int current_time = 0; // start time

    for (int i = 0; i < n; i++)
    {
        if (arrival_time[i] > current_time)
        {
            current_time = arrival_time[i];
        }

        waiting_time[i] = current_time - arrival_time[i];
        total_waiting_time += waiting_time[i];
        current_time += burst_time[i];
    }

    return total_waiting_time;
}

void calculate_turnaround_times(int burst_time[], int waiting_time[], int turnaround_time[], int n)
{
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

float calculate_average_waiting_time(int waiting_time[], int n)
{
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
    }

    float average_waiting_time = (float)total_waiting_time / n;
    return average_waiting_time;
}

float calculate_average_turnaround_time(int turnaround_time[], int n)
{
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += turnaround_time[i];
    }

    float average_turnaround_time = (float)total_turnaround_time / n;
    return average_turnaround_time;
}

int main()
{
    // int pid[] = {1, 2, 3, 4, 5};
    // int arrival_time[] = {0, 4, 7, 12, 15};
    // int burst_time[] = {10, 5, 2, 8, 3};
    // Average Waiting Time: 5.80
    // Average Turnaround Time: 11.40
    //     int pid[] = {1, 2, 3};
    //     int arrival_time[] = {2, 5, 6};
    //     int burst_time[] = {3, 6, 7};
    //     Average Waiting Time: 1.67
    // Average Turnaround Time: 7.00
    int pid[] = {1, 2, 3};
    int arrival_time[] = {0, 5, 7};
    int burst_time[] = {2, 3, 3};
    //     Average Waiting Time: 0.33 cpu idle
    //     Average Turnaround Time: 3.00
    int n = sizeof(pid) / sizeof(pid[0]);
    int waiting_time[n];
    int turnaround_time[n];

    int total_waiting_time = calculate_waiting_times(pid, arrival_time, burst_time, waiting_time, n);
    float average_waiting_time = calculate_average_waiting_time(waiting_time, n);

    calculate_turnaround_times(burst_time, waiting_time, turnaround_time, n);
    float average_turnaround_time = calculate_average_turnaround_time(turnaround_time, n);

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
