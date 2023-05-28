#include <bits/stdc++.h>

using namespace std;

typedef struct process {
    string name;
    int arrivalTime, burstTime, waitingTime, finishTime, turnAroundTime;
    bool operator<(const process &p) const {
        return arrivalTime < p.arrivalTime;
    }
} process;
/*
Input:
4
one 4 5
two 3 6
three 2 1
four 6 7
*/

int main() {
    int n, totalTurnAround = 0, totalWaiting = 0;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<process> processes(n);
    for (auto &p : processes) {
        cout << "Enter process name, arrival time and burst time: ";
        cin >> p.name >> p.arrivalTime >> p.burstTime;
    }
    sort(processes.begin(), processes.end());
    int currentTime = 0;
    for (auto &p : processes) {
        p.waitingTime = currentTime - p.arrivalTime;
        if (p.waitingTime < 0) {
            p.waitingTime = 0;
            p.finishTime = p.arrivalTime + p.burstTime;
        } else {
            p.finishTime = currentTime + p.burstTime;
        }
        p.turnAroundTime = p.finishTime - p.arrivalTime;
        currentTime = p.finishTime;
        totalTurnAround += p.turnAroundTime;
        totalWaiting += p.waitingTime;
    }
    cout << "Process"
         << setw(8) << "Arrival"
         << setw(8) << "Burst"
         << setw(8) << "Waiting"
         << setw(8) << "Finish"
         << setw(8) << "TAT" << endl;
    for (auto p : processes) {
        cout << setw(7) << p.name
             << setw(8) << p.arrivalTime
             << setw(8) << p.burstTime
             << setw(8) << p.waitingTime
             << setw(8) << p.finishTime
             << setw(8) << p.turnAroundTime << endl;
    }
    cout << "Average waiting time: " << (double)totalWaiting / n << endl;
    cout << "Average turn around time: " << (double)totalTurnAround / n << endl;
}