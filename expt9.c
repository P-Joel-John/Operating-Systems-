//cpu scheduling
#include <stdio.h>

#define MAX 10
#define Q 3

/* FCFS  */
float fcfs(int n, int at[], int bt[]) {
int time = 0, wt[MAX];
float total = 0;

for(int i=0;i<n;i++){  
    if(time < at[i])  
        time = at[i];  

    wt[i] = time - at[i];  
    time += bt[i];  
    total += wt[i];  
}  
return total/n;

}

/*  SRTF  */
float srtf(int n, int at[], int bt[]) {
int rt[MAX], wt[MAX], ct[MAX];
int time=0, completed=0;
float total=0;

for(int i=0;i<n;i++)  
    rt[i]=bt[i];  

while(completed<n){  
    int min=9999, idx=-1;  

    for(int i=0;i<n;i++){  
        if(at[i]<=time && rt[i]>0 && rt[i]<min){  
            min=rt[i];  
            idx=i;  
        }  
    }  

    if(idx==-1){  
        time++;  
        continue;  
    }  

    rt[idx]--;  
    time++;  

    if(rt[idx]==0){  
        completed++;  
        ct[idx]=time;  
        wt[idx]=ct[idx]-at[idx]-bt[idx];  
        total+=wt[idx];  
    }  
}  
return total/n;

}

/*  Non Preemptive, Priority  */
float priority(int n, int at[], int bt[], int pr[]) {
int done[MAX]={0}, wt[MAX];
int time=0, completed=0;
float total=0;

while(completed<n){  //higher no,higher priority
    int high=-1, idx=-1;  

    for(int i=0;i<n;i++){  
        if(at[i]<=time && !done[i] && pr[i]>high){  
            high=pr[i];  
            idx=i;  
        }  
    }  

    if(idx==-1){  
        time++;  
        continue;  
    }  

    wt[idx]=time-at[idx];  
    time+=bt[idx];  
    total+=wt[idx];  
    done[idx]=1;  
    completed++;  
}  
return total/n;

}

/*  Round Robin  */
float round_robin(int n, int at[], int bt[]) {
int rt[MAX], wt[MAX], ct[MAX];
int time=0, completed=0;
float total=0;

for(int i=0;i<n;i++)  
    rt[i]=bt[i];  

while(completed<n){  
    int progress=0;  

    for(int i=0;i<n;i++){  
        if(at[i]<=time && rt[i]>0){  
            progress=1;  

            if(rt[i]>Q){  
                time+=Q;  
                rt[i]-=Q;  
            }  
            else{  
                time+=rt[i];  
                ct[i]=time;  
                wt[i]=ct[i]-at[i]-bt[i];  
                total+=wt[i];  
                rt[i]=0;  
                completed++;  
            }  
        }  
    }  

    if(!progress)  
        time++;  
}  
return total/n;

}

/*  MAIN  */
int main(){
int n;
int at[MAX], bt[MAX], pr[MAX];

printf("Enter number of processes: ");  
scanf("%d",&n);  

for(int i=0;i<n;i++){  
    printf("\nProcess %d\n",i+1);  
    printf("Arrival Time: ");  
    scanf("%d",&at[i]);  
    printf("Burst Time: ");  
    scanf("%d",&bt[i]);  
    printf("Priority: ");  
    scanf("%d",&pr[i]);  
}  

float avg1 = fcfs(n,at,bt);  
float avg2 = srtf(n,at,bt);  
float avg3 = priority(n,at,bt,pr);  
float avg4 = round_robin(n,at,bt);  

printf("\nAverage Waiting Time:\n");  
printf("FCFS       = %.2f\n",avg1);  
printf("SRTF       = %.2f\n",avg2);  
printf("Priority   = %.2f\n",avg3);
printf("Round Robin= %.2f\n",avg4);  

printf("\nMinimum Waiting Time Algorithm: ");  

if(avg2<=avg1 && avg2<=avg3 && avg2<=avg4)  
    printf("SRTF\n");  
else if(avg1<=avg3 && avg1<=avg4)  
    printf("FCFS\n");  
else if(avg3<=avg4)  
    printf("Priority\n");  
else  
    printf("Round Robin\n");  

return 0;

}
