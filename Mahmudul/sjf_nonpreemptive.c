#include<stdio.h>

typedef struct {
    char name[20];
    int arrivalTime;
    int startTime;
    int endTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
} Process;

int initial = 1;
int cmp(Process a, Process b) {
    if (initial) {
        if (a.arrivalTime > b.arrivalTime) return 1;
    } else {
        if (a.burstTime > b.burstTime) return 1;
    }
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void bubble_sort(Process *arr, int start_idx, int end_idx) {
    Process temp;
    for (int i = start_idx; i < end_idx; i++) {
        for (int j = start_idx; j < end_idx - 1; j++) {
            if (cmp(arr[j], arr[j + 1])) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, totalWaitingTime = 0, totalTurnAroundTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the name of the process: ");
        scanf("%s", p[i].name);
        printf("Enter the arrival time of the process %s: ", p[i].name);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter the burst time of the process %s: ", p[i].name);
        scanf("%d", &p[i].burstTime);
    }

    bubble_sort(p, 0, n);
    initial = 0;

    for (int i = 0; i < n; i++) {
        int nextStart;
        if (i == 0) {
            nextStart = p[i].arrivalTime;
        } else {
            nextStart = max(p[i].arrivalTime, p[i - 1].endTime);
        }
        int consider_till = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrivalTime <= nextStart) {
                consider_till = j;
            } else {
                break;
            }
        }
        bubble_sort(p, i, consider_till + 1);

        p[i].startTime = nextStart;
        p[i].endTime = p[i].startTime + p[i].burstTime;
        p[i].waitingTime = p[i].startTime - p[i].arrivalTime;
        p[i].turnAroundTime = p[i].endTime - p[i].arrivalTime;

        totalWaitingTime += p[i].waitingTime;
        totalTurnAroundTime += p[i].turnAroundTime;
    }

    printf("\nProcess  AT  BT  ST  ET  WT  TAT:\n");
    for (int i = 0; i < n; i++) {
        printf("%7s%4d%4d%4d%4d%4d%5d\n", p[i].name, p[i].arrivalTime, p[i].burstTime, p[i].startTime, p[i].endTime, p[i].waitingTime, p[i].turnAroundTime);
    }
    printf("Average waiting time: %f\n", (float)totalWaitingTime / n);
    printf("Average turn around time: %f\n", (float)totalTurnAroundTime / n);
    return 0;
}
