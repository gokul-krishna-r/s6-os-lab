#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Process{
	int pid;
	int arrT;
	int burstT;
	int turnT;
	int waitT;
	int compT;
	int remain;
};

int main(){
	struct Process processes[20];
	int p,timeQ;
	int count=0;
	int turn=0;
	printf("Enter the number of processes: ");
    scanf("%d", &p);
    printf("Enter quantum: ");
    scanf("%d", &timeQ);
	printf("Enter arrival time and Burst Time:\n");
    for(int i=0;i<p;i++){
		printf("%d: ",i+1);
		scanf("%d%d",&processes[i].arrT,&processes[i].burstT);
		processes[i].remain=processes[i].burstT;
		processes[i].pid=i+1;

    }
    
    struct Process temp;
     for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < (p - 1-i); j++)
        {
            if (processes[j].arrT > processes[j + 1].arrT)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            } 
        }
    }
    int flag=0;
    int i=0;
    count=p;
    for(turn=0,i=0;count!=0;i=(i+1)%p){
    		if(processes[i].arrT>turn){
    			continue;
    		}
   		
    		if(processes[i].remain <= timeQ && processes[i].remain >0){
    		    flag=1;
    			turn+=processes[i].remain;
    			processes[i].remain=0;

    		}else if(processes[i].remain>0){
    			turn+=timeQ;
				processes[i].remain-=timeQ;
    		}
    		
    		if(processes[i].remain==0 && flag==1){
    			count--;
    			processes[i].compT=turn;
    			processes[i].turnT=processes[i].compT-processes[i].arrT;
    			processes[i].waitT=processes[i].turnT-processes[i].burstT;
    printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d\n", processes[i].pid, processes[i].burstT, processes[i].turnT,processes[i].waitT);

    			flag=0;
    		}
    		
    		
	
    }
    
    return 0;
 }
  

