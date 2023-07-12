#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void main(){
    int PriorT[20],BurstT[20];
    int WaitT[20],TurnT[20];
    float AvgWaitT=0,AvgTurnT=0;
    int p;
    int pid[20];
    int fid[20];

    WaitT[0]=0; //Waiting time of initial process is 0

    printf("Enter number of processes required: ");
    scanf("%d",&p);
    
    printf("Enter Burst and Prioirty of %d processes:\n   Burst Time\tPrioirty\n",p);
    
    for(int i=0;i<p;i++){

        printf("%d: " ,i+1);
        scanf("%d%d",&BurstT[i],&PriorT[i]);
        pid[i]=i;
    }

    //sorting based on priority
    for(int i=0;i<p;i++){
        for(int j=0;j<p-i-1;j++){
            if(PriorT[j]>PriorT[j+1]){
                int temp=PriorT[j];
                PriorT[j]=PriorT[j+1];
                PriorT[j+1]=temp;
                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
                temp=BurstT[j];
                BurstT[j]=BurstT[j+1];
                BurstT[j+1]=temp;
            }
        }
    }

    //Calculating Waiting Time
    for(int i=1;i<p;i++){
        WaitT[i]=WaitT[i-1]+BurstT[i-1];
    }

    //Calculating TurnAround Time
    for(int i=0;i<p;i++){
        TurnT[i]=BurstT[i]+WaitT[i];
        AvgWaitT+=WaitT[i];
        AvgTurnT+=TurnT[i];    
    }
    

    printf("Si No: Priority\t\tBurst Time\tWaiting time\tTurnAround Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",pid[i]+1,PriorT[i],BurstT[i],WaitT[i],TurnT[i]);
        
    }
     printf("Avgerage Waiting Time: %f \n Average Turnaround Time: %f\n",AvgWaitT/p,AvgTurnT/p);

}

