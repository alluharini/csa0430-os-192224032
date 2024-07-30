#include <stdio.h>
#include <limits.h>
struct Process {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int rt;
    int ct;
};
void findWaitingTimeNonPreemptive(struct Process proc[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        int minBtIndex = -1;
        for (int j = 0; j < n; j++) {
            if (proc[j].at <= currentTime && proc[j].rt > 0 && (minBtIndex == -1 || proc[j].bt < proc[minBtIndex].bt)) {
                minBtIndex = j;
            }
        }
        currentTime = currentTime + proc[minBtIndex].bt;
        proc[minBtIndex].wt = currentTime - proc[minBtIndex].at - proc[minBtIndex].bt;
        proc[minBtIndex].tat = currentTime - proc[minBtIndex].at;
        proc[minBtIndex].rt = 0;
    }
}
void findWaitingTimePreemptive(struct Process proc[], int n) {
    int complete = 0, t = 0, minBt = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;
    for (int i = 0; i < n; i++)
        proc[i].rt = proc[i].bt;
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].at <= t) && (proc[j].rt < minBt) && proc[j].rt > 0) {
                minBt = proc[j].rt;
                shortest = j;
                check = 1;
            }
        }
        if (check == 0) {
            t++;
            continue;
        }
        proc[shortest].rt--;
        minBt = proc[shortest].rt;
        if (minBt == 0)
            minBt = INT_MAX;
        if (proc[shortest].rt == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;
            proc[shortest].wt = finish_time - proc[shortest].bt - proc[shortest].at;
            proc[shortest].tat = finish_time - proc[shortest].at;
        }
        t++;
    }
}
void findAvgTime(struct Process proc[], int n, int isPreemptive) {
    if (isPreemptive) {
        findWaitingTimePreemptive(proc, n);
    } else {
        findWaitingTimeNonPreemptive(proc, n);
    }
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("Processes   Burst time   Arrival time   Waiting time   Turn around time\n");
    for (int i = 0; i < n; i++) {
        printf("%d           %d           %d             %d               %d\n", proc[i].pid, proc[i].bt, proc[i].at, proc[i].wt, proc[i].tat);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}
int main() {
    struct Process proc[] = {{1, 6, 2}, {2, 8, 5}, {3, 7, 1}, {4, 3, 0}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int choice;
    printf("Choose Scheduling Algorithm:\n1. Non-Preemptive SJF\n2. Preemptive SJF\n");
    scanf("%d", &choice);
    findAvgTime(proc, n, choice == 2);
    return 0;
}
