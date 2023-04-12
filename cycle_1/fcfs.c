#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void main(){
    int ArrT[20],BurstT[20];
    int WaitT[20],TurnT[20];
    int p;
    int pid[20];

    WaitT[0]=0; //Waiting time of initial process is 0

    printf("Enter number of processes required: ");
    scanf("%d",&p);
    
    printf("Enter Burst and Arrival Time of %d processes:\n   Burst Time\tArrival time\n",p);
    
    for(int i=0;i<p;i++){
        printf("%d: " ,i+1);
        scanf("%d%d",&BurstT[i],&ArrT[i]);
    }
     //Calculating TurnAround Time
    int completionTime=0;
    for(int i=0;i<p;i++){
        completionTime+=BurstT[i];
        TurnT[i]=completionTime-ArrT[i];
    }
    //Calculating Waiting Time
    for(int i=1;i<p;i++){
        WaitT[i]=TurnT[i]-BurstT[i];
    }
    
    for(int i=0;i<p;i++){
      pid[i]=fork();
      if(pid[i]==0){
           sleep(ArrT[i]);
           printf("Process %d started\n",i+1);
           float delay=500000;
           while(delay>0){
            delay--;
           }
           printf("Process %d stopped\n",i+1);
           exit(0);
      } 
    else{
        waitpid(pid[i],NULL,0);
        }
    }
    
   
    printf("Si No:\tArrival Time\tBurst Time\tWaiting time\tTurnAround Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,ArrT[i],BurstT[i],WaitT[i],TurnT[i]);
        
    }

}

