#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int pid, arrival, burst, remaining;
    int completion, waiting, turnaround;
    int type; // 0 = system, 1 = user
} Process;

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void init(Queue *q) { q->front = q->rear = -1; }

int isEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return val;
}

void sort(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrival > p[j].arrival) {
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
}

int main() {
    int n;
    Process p[MAX];
    Queue sysQ, userQ;

    init(&sysQ); init(&userQ);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter burst time: ");
        scanf("%d", &p[i].burst);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].pid = i;
        p[i].remaining = p[i].burst;
    }


    int time = 0, completed = 0, i = 0;
    int current = -1;

    while (completed < n) {

        while (i < n && p[i].arrival <= time) {
            if (p[i].type == 0)
                enqueue(&sysQ, i);
            else
                enqueue(&userQ, i);
            i++;
        }

        if (current != -1 && p[current].type == 1 && !isEmpty(&sysQ)) {
            enqueue(&userQ, current);
            current = -1;
        }

        if (current == -1) {
            if (!isEmpty(&sysQ))
                current = dequeue(&sysQ);
            else if (!isEmpty(&userQ))
                current = dequeue(&userQ);
            else {
                time++;
                continue;
            }
        }

        p[current].remaining--;
        time++;

        if (p[current].remaining == 0) {
            p[current].completion = time;
            completed++;
            current = -1;
        }
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;

        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].type == 0 ? "System" : "User",
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
