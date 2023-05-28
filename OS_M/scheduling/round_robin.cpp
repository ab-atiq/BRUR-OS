#include <bits/stdc++.h>

using namespace std;

typedef struct process {
    string name;
    int burstTime, temBurst, waitingTime, finishTime, turnAroundTime;
} process;
/*
Input:
4 2
one 5
two 6
three 1
four 7


*/

int main() {
    int n, quantum, totalTime = 0, totalTurnAround = 0, totalWaiting = 0;
    cout << "Enter number of processes and quantum: ";
    cin >> n >> quantum;
    vector<process> processes(n);
    for (auto &p : processes) {
        cout << "Enter process name and burst time: ";
        cin >> p.name >> p.burstTime;
        totalTime += p.burstTime;
        p.temBurst = p.burstTime;
    }

    int currentTime = 0;
    while (currentTime < totalTime) {
        for (auto &p : processes) {
            if (p.temBurst > 0) {
                if (p.temBurst > quantum) {
                    currentTime += quantum;
                    p.temBurst -= quantum;
                } else {
                    currentTime += p.temBurst;
                    p.waitingTime = currentTime - p.burstTime;
                    p.temBurst = 0;
                    p.finishTime = currentTime;
                    p.turnAroundTime = p.finishTime;
                    totalTurnAround += p.turnAroundTime;
                    totalWaiting += p.waitingTime;
                }
            }
        }
    }
    cout << "Process"
         << setw(8) << "Burst"
         << setw(8) << "Waiting"
         << setw(8) << "Finish"
         << setw(8) << "TAT" << endl;
    for (auto p : processes) {
        cout << setw(7) << p.name
             << setw(8) << p.burstTime
             << setw(8) << p.waitingTime
             << setw(8) << p.finishTime
             << setw(8) << p.turnAroundTime << endl;
    }
    cout << "Average waiting time: " << (double)totalWaiting / n << endl;
    cout << "Average turn around time: " << (double)totalTurnAround / n << endl;
}