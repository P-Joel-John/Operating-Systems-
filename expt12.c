
//deadlock Detection
#include <stdio.h>
#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX];
    int finish[MAX];
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Initialize finish
    for(i = 0; i < n; i++) {
        int flag = 0;
        for(j = 0; j < m; j++)
            if(alloc[i][j] != 0)
                flag = 1;

        if(flag == 0)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    // Deadlock Detection
    int done;
    do {
        done = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                for(j = 0; j < m; j++)
                    if(request[i][j] > avail[j])
                        break;

                if(j == m) {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    finish[i] = 1;
                    done = 1;
                }
            }
        }
    } while(done);

    // Check deadlock
    int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("Process P%d is deadlocked\n", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
        printf("No deadlock detected\n");

    return 0;
}
