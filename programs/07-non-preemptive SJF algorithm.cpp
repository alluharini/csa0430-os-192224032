#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    proc[0].turnaround_time = proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void sortProcessesByBurstTime(struct Process proc[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (proc[j].burst_time > proc[j+1].burst_time) {
                struct Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
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
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i+1;
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &proc[i].burst_time);
    }

    sortProcessesByBurstTime(proc, n);
    calculateTimes(proc, n);
    printProcesses(proc, n);

    return 0;
}

