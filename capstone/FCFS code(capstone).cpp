#include <stdio.h>
struct Process {
    int pid;
    int bt;
    int wt;
    int tat;
};
void findWaitingTime(struct Process proc[], int n) {
    proc[0].wt = 0;
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i-1].wt + proc[i-1].bt;
    }
}
void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}
void findAvgTime(struct Process proc[], int n) {
    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("Processes   Burst time   Waiting time   Turn around time\n");
    for (int i = 0; i < n; i++) {
        printf("%d           %d           %d               %d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}
int main() {
    struct Process proc[] = {{1, 24}, {2, 3}, {3, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    findAvgTime(proc, n);
    return 0;
}
