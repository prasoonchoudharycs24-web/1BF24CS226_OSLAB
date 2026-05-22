#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
} Process;


/* Calculate CPU Utilization */
float calculateUtilization(Process p[], int n) {
    float u = 0;

    for(int i = 0; i < n; i++) {
        u += (float)p[i].bt / p[i].period;
    }

    return u;
}


/* Calculate RM Bound */
float rmBound(int n) {
    return n * (pow(2, 1.0/n) - 1);
}


/* Sort by Deadline (EDF) */
void sortEDF(Process p[], int n) {

    for(int i = 0; i < n-1; i++) {

        for(int j = i+1; j < n; j++) {

            if(p[i].deadline > p[j].deadline) {

                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;

            }
        }
    }
}


/* Sort by Period (RMS) */
void sortRM(Process p[], int n) {

    for(int i = 0; i < n-1; i++) {

        for(int j = i+1; j < n; j++) {

            if(p[i].period > p[j].period) {

                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;

            }
        }
    }
}


/* Reassign IDs after sorting */
void reassignIDs(Process p[], int n) {

    for(int i = 0; i < n; i++) {
        p[i].id = i;
    }
}


/* Calculate CT, WT, TAT */
void calculateTimes(Process p[], int n) {

    int time = 0;

    for(int i = 0; i < n; i++) {

        time += p[i].bt;

        p[i].ct = time;

        p[i].tat = p[i].ct;

        p[i].wt = p[i].tat - p[i].bt;

    }
}


/* Print EDF */
void printEDF(Process p[], int n) {

    float util = calculateUtilization(p, n);

    printf("\n====== Earliest Deadline First (EDF) Scheduling ======\n");

    printf("CPU Utilization: %.2f\n", util);

    if(util <= 1)
        printf("Schedulable (Utilization <= 1)\n");

    else {

        printf("NOT Schedulable (Utilization > 1)\n");

        return;

    }

    sortEDF(p, n);

    reassignIDs(p, n);   // FIX

    calculateTimes(p, n);

    printf("ID  BF  Deadline  CT  WT  TAT\n");

    for(int i = 0; i < n; i++) {

        printf("%d   %d   %d        %d   %d   %d\n",

               p[i].id,

               p[i].bt,

               p[i].deadline,

               p[i].ct,

               p[i].wt,

               p[i].tat);

    }
}


/* Print RMS */
void printRM(Process p[], int n) {

    float util = calculateUtilization(p, n);

    float bound = rmBound(n);

    printf("\n====== Rate Monotonic Scheduling (RMS) ======\n");

    printf("CPU Utilization: %.2f\n", util);

    printf("RM Bound: %.4f\n", bound);

    if(util <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");

    else {

        printf("NOT Schedulable (Utilization > RM Bound)\n");

        return;

    }

    sortRM(p, n);

    reassignIDs(p, n);   // FIX

    calculateTimes(p, n);

    printf("ID  BF  Period  CT  WT  TAT\n");

    for(int i = 0; i < n; i++) {

        printf("%d   %d   %d      %d   %d   %d\n",

               p[i].id,

               p[i].bt,

               p[i].period,

               p[i].ct,

               p[i].wt,

               p[i].tat);

    }
}


/* Main Function */
int main() {

    Process p[MAX];

    int n;

    printf("Enter number of processes: ");

    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for(int i = 0; i < n; i++) {

        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);

    }


    Process edf[MAX], rm[MAX];


    /* Copy arrays */

    for(int i = 0; i < n; i++) {

        edf[i] = p[i];

        rm[i] = p[i];

    }


    printEDF(edf, n);

    printRM(rm, n);

    return 0;

}
