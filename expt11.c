//bankers algorithm
#include <stdio.h>
#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX];
    int finish[MAX] = {0}, safeSeq[MAX];
    int i, j, k, count = 0;//count of processes in safe sequence

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    //  Need Matrix allocation
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j]-alloc[i][j];
        
    printf("need matrix\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    int work[n];//work array
        for(j = 0; j < m; j++){          
            work[j] = avail[j];
        }
    //Safety Algorithm
    while(count < n) {//Find an index of a process which is not finished and whose needs can be satisfied with current available resources
        int found = 0;//flag whether atleast  1 process  executes in this loop  

          for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                for(j = 0; j < m; j++){
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == m) {//If all needs of process i are satisfied
                    for(k = 0; k < m; k++){
                        work[k] += alloc[i][k];
                    }
                        safeSeq[count++] = i;
                        finish[i] = 1;
                        found = 1;
                }
            }
        }
        if(found == 0) {//If no such process is found, then system is not in safe state
            printf("System is NOT in a safe state,therefore no safe sequence exists\n");
            return 0;//exit the program
        }
    }

    printf("System is in safe state.\nSafe sequence: ");
    for(i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    return 0;
}
