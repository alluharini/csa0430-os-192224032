#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].turnaround_time = time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i+1;
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}

