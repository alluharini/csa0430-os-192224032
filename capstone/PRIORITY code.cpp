
#include <stdio.h>
#include <limits.h>
struct Process {
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int rt;
    int priority;
};
void findWaitingTimeNonPreemptive(struct Process proc[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        int highestPriorityIndex = -1;
        for (int j = 0; j < n; j++) {
            if (proc[j].at <= currentTime && proc[j].rt > 0 && (highestPriorityIndex == -1 || proc[j].priority < proc[highestPriorityIndex].priority)) {
                highestPriorityIndex = j;
            }
        }
        currentTime += proc[highestPriorityIndex].bt;
        proc[highestPriorityIndex].wt = currentTime - proc[highestPriorityIndex].at - proc[highestPriorityIndex].bt;
        proc[highestPriorityIndex].tat = currentTime - proc[highestPriorityIndex].at;
        proc[highestPriorityIndex].rt = 0;
    }
}
void findWaitingTimePreemptive(struct Process proc[], int n) {
    int complete = 0, t = 0, minPriority = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;
    for (int i = 0; i < n; i++)
        proc[i].rt = proc[i].bt;
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].at <= t) && (proc[j].priority < minPriority) && proc[j].rt > 0) {
                minPriority = proc[j].priority;
                shortest = j;
                check = 1;
            }
        }
        if (check == 0) {
            t++;
            continue;
        }
        proc[shortest].rt--;
        minPriority = proc[shortest].rt > 0 ? proc[shortest].priority : INT_MAX;
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
    printf("Processes   Burst time   Arrival time   Priority   Waiting time   Turn around time\n");
    for (int i = 0; i < n; i++) {
        printf("%d           %d           %d             %d         %d               %d\n", proc[i].pid, proc[i].bt, proc[i].at, proc[i].priority, proc[i].wt, proc[i].tat);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}
int main() {
    struct Process proc[] = {{1, 10, 0, 0, 0, 10}, {2, 1, 1, 0, 0, 3}, {3, 2, 2, 0, 0, 2}, {4, 1, 3, 0, 0, 1}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int choice;
    printf("Choose Scheduling Algorithm:\n1. Non-Preemptive Priority\n2. Preemptive Priority\n");
    scanf("%d", &choice);
    findAvgTime(proc, n, choice == 2);
    return 0;
}

