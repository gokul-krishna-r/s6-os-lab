#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
    int BurstT[20],BurstT2[20];
    int WaitT[20],TurnT[20];
    int p;
    int TimeQ,turn=0;
    float AvgWaitT=0,AvgTurnT=0;
    int pid[20];
    int count=0;

    WaitT[0]=0;

    printf("Enter number of processes required: ");
    scanf("%d",&p);
    printf("Enter Time Quantum: ");
    scanf("%d",&TimeQ);
    
    printf("Enter Burst and Arrival Time of %d processes:\n   Burst Time\n",p);
    
    for(int i=0;i<p;i++){
        printf("%d: " ,i+1);
        scanf("%d",&BurstT[i]);
        BurstT2[i]=BurstT[i];
        pid[i]=i;
    }
    
      for(int i=0;i<p;i++){
            TurnT[i]=0;
            WaitT[i]=0;
        }
    for(;;){
        //Calculating TurnAround Time
        count=0;
        for(int i=0;i<p;i++){
            
            if(BurstT2[i]<=0){
                count++;
                continue;
            }
           if(TimeQ > BurstT2[i]){
                TurnT[i]=BurstT2[i]+turn;
                turn+=BurstT2[i];
                BurstT2[i]=0;

            }else{
                TurnT[i]=TimeQ+turn;
                BurstT2[i]=BurstT2[i]-TimeQ;
                turn+=TimeQ;
            }
        }
        if(count==p){
            break;
        }
     }

    for(int i=0;i<p;i++){
        WaitT[i]=TurnT[i]-BurstT[i];
        AvgWaitT+=WaitT[i];
        AvgTurnT+=TurnT[i];  
    }
    printf("Si No:\tBurst Time\tWaiting time\tTurnAround Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d\t%d\t\t%d\t\t%d\n",pid[i]+1,BurstT[i],WaitT[i],TurnT[i]);     
    }
    printf("Avgerage Waiting Time: %f \n Average Turnaround Time: %f\n",AvgWaitT/p,AvgTurnT/p);
}

