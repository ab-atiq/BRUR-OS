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

int main() {
    int n, totalWaitingTime = 0, totalTurnAroundTime = 0;
    int timeQuanta = 0, totalBurstTime = 0, elapsedTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quanta: ");
    scanf("%d", &timeQuanta);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the name of the process: ");
        scanf("%s", p[i].name);
        printf("Enter the burst time of the process %s: ", p[i].name);
        scanf("%d", &p[i].burstTime);
        totalBurstTime += p[i].burstTime;
    }
    Process copy[n];
    for (int i = 0; i < n; i++) {
        copy[i] = p[i];
    }

    while (elapsedTime < totalBurstTime) {
        for (int i = 0; i < n; i++) {
            if (p[i].burstTime > 0) {
                if (p[i].burstTime > timeQuanta) {
                    p[i].burstTime -= timeQuanta;
                    elapsedTime += timeQuanta;
                    printf("%s ----> %d\n", p[i].name, timeQuanta);
                } else {
                    elapsedTime += p[i].burstTime;
                    printf("%s ----> %d\n", p[i].name, timeQuanta);
                    p[i].endTime = elapsedTime;
                    p[i].burstTime = 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        p[i].burstTime = copy[i].burstTime;
        p[i].turnAroundTime = p[i].endTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
        totalWaitingTime += p[i].waitingTime;
        totalTurnAroundTime += p[i].turnAroundTime;
    }

    printf("\nProcess  BT  ET  WT  TAT:\n");
    for (int i = 0; i < n; i++) {
        printf("%7s%4d%4d%4d%5d\n", p[i].name, p[i].burstTime, p[i].endTime, p[i].waitingTime, p[i].turnAroundTime);
    }
    printf("Average waiting time: %f\n", (float) totalWaitingTime / n);
    printf("Average turn around time: %f\n", (float) totalTurnAroundTime / n);
    printf("Total Estimated Time: %d\n", elapsedTime);
    return 0;
}
