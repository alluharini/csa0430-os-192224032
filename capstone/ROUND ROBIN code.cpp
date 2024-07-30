#include <stdio.h>

int main() {
    int i, NOP, sum = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
    printf(" Total number of process in the system: ");
    scanf("%d", &NOP);
    y = NOP;
    for (i = 0; i < NOP; i++) {
        printf("\n Enter Arrival and Burst time of Process[%d]: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        temp[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &quant);
    printf("\n Process No \t Burst Time \t TAT \t Waiting Time ");
    for (sum = i = 0; y != 0;) {
        if (temp[i] <= quant && temp[i] > 0) { sum += temp[i]; temp[i] = 0; }
        else if (temp[i] > 0) { temp[i] -= quant; sum += quant; }
        if (temp[i] == 0 && temp[i] != -1) {
            y--; printf("\nProcess[%d] \t %d \t\t %d \t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt += sum - at[i] - bt[i]; tat += sum - at[i]; temp[i] = -1;
        }
        i = (i == NOP - 1) ? 0 : ((at[i + 1] <= sum) ? i + 1 : 0);
    }
    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;
    printf("\n Average Turn Around Time: %f", avg_tat);
    printf("\n Average Waiting Time: %f\n", avg_wt);
    return 0;
}
