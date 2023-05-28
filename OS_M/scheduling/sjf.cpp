#include <bits/stdc++.h>

using namespace std;

typedef struct process {
    string name;
    int arrival, burstTime, waitingTime, finishTime, turnAroundTime;
    bool operator<(const process &p) const {
        return -burstTime < -p.burstTime;
    }
} process;

bool compareArrival(process &a, process &b) {
    if (a.arrival == b.arrival) {
        return a.burstTime < b.burstTime;
    }
    return a.arrival < b.arrival;
}
/*
Input:
4
one 1 5
two 1 6
three 2 1
four 2 7


*/

int main() {
    int n, totalTurnAround = 0, totalWaiting = 0;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<process> processes(n);
    for (auto &p : processes) {
        cout << "Enter process name, arrival and burst time: ";
        cin >> p.name >> p.arrival >> p.burstTime;
    }
    sort(processes.begin(), processes.end(), compareArrival);
    priority_queue<process> pq;
    cout << "Process"
         << setw(8) << "Arrival"
         << setw(8) << "Burst"
         << setw(8) << "Waiting"
         << setw(8) << "Finish"
         << setw(8) << "TAT" << endl;
    int currentTime = 0;
    for (int i = 0; i < n || !pq.empty();) {
        if (pq.empty()) {
            currentTime = processes[i].arrival;
            while (i < n && processes[i].arrival <= currentTime) {
                pq.emplace(processes[i]);
                i++;
            }
        }
        process p = pq.top();
        pq.pop();
        p.waitingTime = currentTime - p.arrival;
        p.finishTime = currentTime + p.burstTime;
        p.turnAroundTime = p.finishTime - p.arrival;
        currentTime = p.finishTime;
        totalTurnAround += p.turnAroundTime;
        totalWaiting += p.waitingTime;
        while (i < n && processes[i].arrival <= currentTime) {
            pq.emplace(processes[i]);
            i++;
        }
        cout << setw(7) << p.name
             << setw(8) << p.arrival
             << setw(8) << p.burstTime
             << setw(8) << p.waitingTime
             << setw(8) << p.finishTime
             << setw(8) << p.turnAroundTime << endl;
    }
    cout << "Average waiting time: " << (double)totalWaiting / n << endl;
    cout << "Average turn around time: " << (double)totalTurnAround / n << endl;
}