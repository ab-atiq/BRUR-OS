// all okey
#include <stdio.h>

void round_robin(int pid[], int burst_time[], int n, int time_quantum)
{
    int remaining_time[n];
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = burst_time[i];
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                if (remaining_time[i] <= time_quantum)
                {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    int waiting_time = current_time - burst_time[i];
                    int turnaround_time = current_time;

                    printf("Process %d:\n", pid[i]);
                    printf("Waiting Time: %d\n", waiting_time);
                    printf("Turnaround Time: %d\n\n", turnaround_time);

                    completed++;
                }
                else
                {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }
}

float calculate_average(int times[], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total += times[i];
    }

    float average = (float)total / n;
    return average;
}

int main()
{
    // int pid[] = {1, 2, 3, 4, 5};
    // int burst_time[] = {8, 4, 9, 5, 3};
    int pid[] = {1, 2, 3, 4};
    int burst_time[] = {3, 4, 1, 6};

    int n = sizeof(pid) / sizeof(pid[0]);
    int time_quantum = 2;

    round_robin(pid, burst_time, n, time_quantum);

    return 0;
}
