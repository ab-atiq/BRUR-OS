// #include <stdio.h>
// #include <stdbool.h>
// #include <limits.h>
// void sjf_preemptive(int pid[], int arrival_time[], int burst_time[], int n)
// {
//     int remaining_time[n];
//     for (int i = 0; i < n; i++)
//     {
//         remaining_time[i] = burst_time[i];
//     }

//     int completed = 0;
//     int current_time = 0;

//     while (completed != n)
//     {
//         int shortest_job = -1;
//         int shortest_burst = INT_MAX;

//         for (int i = 0; i < n; i++)
//         {
//             if (arrival_time[i] <= current_time && remaining_time[i] < shortest_burst && remaining_time[i] > 0)
//             {
//                 shortest_job = i;
//                 shortest_burst = remaining_time[i];
//             }
//         }

//         if (shortest_job == -1)
//         {
//             current_time++;
//             continue;
//         }

//         remaining_time[shortest_job]--;

//         if (remaining_time[shortest_job] == 0)
//         {
//             completed++;
//             int completion_time = current_time + 1;
//             int waiting_time = completion_time - arrival_time[shortest_job] - burst_time[shortest_job];
//             int turnaround_time = completion_time - arrival_time[shortest_job];

//             printf("Process %d:\n", pid[shortest_job]);
//             printf("Completion Time: %d\n", completion_time);
//             printf("Waiting Time: %d\n", waiting_time);
//             printf("Turnaround Time: %d\n\n", turnaround_time);
//         }

//         current_time++;
//     }
// }

// int main()
// {
//     // int pid[] = {1, 2, 3, 4, 5};
//     // int arrival_time[] = {0, 2, 4, 6, 8};
//     // int burst_time[] = {3, 6, 4, 5, 2};

//     // my code
//     int pid[] = {1, 2, 3, 4, 5};
//     int arrival_time[] = {0, 2, 4, 5, 3};
//     int burst_time[] = {7, 4, 1, 4, 5};

//     int n = sizeof(pid) / sizeof(pid[0]);

//     sjf_preemptive(pid, arrival_time, burst_time, n);

//     return 0;
// }

// avarage waiting time and turn around time
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
void sjf_preemptive(int pid[], int arrival_time[], int burst_time[], int n, int waiting_time[], int turnaround_time[])
{
    int remaining_time[n];
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = burst_time[i];
    }

    int completed = 0;
    int current_time = 0;

    while (completed != n)
    {
        int shortest_job = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= current_time && remaining_time[i] < shortest_burst && remaining_time[i] > 0)
            {
                shortest_job = i;
                shortest_burst = remaining_time[i];
            }
        }

        if (shortest_job == -1)
        {
            current_time++;
            continue;
        }

        remaining_time[shortest_job]--;

        if (remaining_time[shortest_job] == 0)
        {
            completed++;
            int completion_time = current_time + 1;
            waiting_time[shortest_job] = completion_time - arrival_time[shortest_job] - burst_time[shortest_job];
            turnaround_time[shortest_job] = completion_time - arrival_time[shortest_job];
        }

        current_time++;
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
    // int arrival_time[] = {0, 2, 4, 6, 8};
    // int burst_time[] = {3, 6, 4, 5, 2};
    // my code
    int pid[] = {1, 2, 3, 4, 5};
    int arrival_time[] = {0, 2, 4, 5, 3};
    int burst_time[] = {7, 4, 1, 4, 5};

    int n = sizeof(pid) / sizeof(pid[0]);

    int waiting_time[n];
    int turnaround_time[n];

    sjf_preemptive(pid, arrival_time, burst_time, n, waiting_time, turnaround_time);

    float average_waiting_time = calculate_average(waiting_time, n);
    float average_turnaround_time = calculate_average(turnaround_time, n);

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
