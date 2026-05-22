#include <stdio.h>

void printFrames(int f[], int n) {
    for(int i = 0; i < n; i++)
        printf(f[i] == -1 ? "- " : "%d ", f[i]);
    printf("\n");
}

void FIFO(int p[], int n, int f) {
    int fr[10], k = 0, faults = 0;

    for(int i = 0; i < f; i++) fr[i] = -1;

    printf("\n--- FIFO ---\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < f; j++)
            if(fr[j] == p[i]) found = 1;

        if(!found) {
            fr[k] = p[i];
            k = (k + 1) % f;
            faults++;

            printf("%d\t", p[i]);
            printFrames(fr, f);
        }
    }

    printf("FIFO Faults = %d\n", faults);
}

void LRU(int p[], int n, int f) {
    int fr[10], t[10] = {0}, faults = 0, cnt = 0;

    for(int i = 0; i < f; i++) fr[i] = -1;

    printf("\n--- LRU ---\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {
        int found = 0, pos = 0;

        for(int j = 0; j < f; j++) {
            if(fr[j] == p[i]) {
                t[j] = ++cnt;
                found = 1;
            }
            if(t[j] < t[pos]) pos = j;
        }

        if(!found) {
            fr[pos] = p[i];
            t[pos] = ++cnt;
            faults++;

            printf("%d\t", p[i]);
            printFrames(fr, f);
        }
    }

    printf("LRU Faults = %d\n", faults);
}

void Optimal(int p[], int n, int f) {
    int fr[10], faults = 0;

    for(int i = 0; i < f; i++) fr[i] = -1;

    printf("\n--- Optimal ---\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < f; j++)
            if(fr[j] == p[i]) found = 1;

        if(!found) {
            int pos = -1, far = i;

            for(int j = 0; j < f; j++) {
                int k;

                if(fr[j] == -1) {
                    pos = j;
                    break;
                }

                for(k = i + 1; k < n; k++)
                    if(fr[j] == p[k]) break;

                if(k > far) {
                    far = k;
                    pos = j;
                }
            }

            fr[pos] = p[i];
            faults++;

            printf("%d\t", p[i]);
            printFrames(fr, f);
        }
    }

    printf("Optimal Faults = %d\n", faults);
}

int main() {
    int p[50], n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    FIFO(p, n, f);
    LRU(p, n, f);
    Optimal(p, n, f);

    return 0;
}
