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
	int priority;
};
int maxof(int a,int b){
	
	return a-b > 0 ? a : b;
}

int main(){
	struct Process processes[20];
	int p;
	int count=0;
	int time=0;
	int greatest=0;
	float wait_time;
	float turnaround_time;
	int turn=0;
	int totTime=0;
	printf("Enter the number of processes: ");
    scanf("%d", &p);
	printf("Enter arrival time and Burst Time and Priority:\n");
	
    for(int i=0;i<p;i++){
		printf("%d: ",i+1);
		scanf("%d%d%d",&processes[i].arrT,&processes[i].burstT,&processes[i].priority);
		processes[i].remain=processes[i].burstT;
		totTime+=processes[i].burstT;
		if(processes[i].arrT<=processes[greatest].arrT){
			greatest=i;
			time=processes[greatest].arrT;
		}
		processes[i].pid=i+1;
    }
    
    int flag=0;
    processes[19].priority=-1;
    
	for(time=time;count!=p;time++){

		greatest=19;
		for(int i=0;i<p;i++){
			if(processes[i].arrT<=time && processes[i].priority > processes[greatest].priority && processes[i].remain>0){
				greatest=i;

			}
		}
		
		if(processes[greatest].remain>0){
			processes[greatest].remain-=1;
			if(processes[greatest].remain==0){
				flag=1;
			}
		}

		if(processes[greatest].remain==0 && flag==1){
			count++;
			processes[greatest].compT = time+1;
    		processes[greatest].turnT = processes[greatest].compT-processes[greatest].arrT;
    		processes[greatest].waitT = processes[greatest].turnT-processes[greatest].burstT;
    		wait_time += processes[greatest].waitT;
            turnaround_time += processes[greatest].turnT;
			flag=0;
    printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", processes[greatest].pid, processes[greatest].burstT, processes[greatest].turnT,processes[greatest].waitT);
		}

		if(count==p){
			break;
		}
	}
	
    printf("Si No:\tArrival Time\tBurst Time\tWaiting time\tTurnAround Time\n");
  
    for(int i=0;i<p;i++){	printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].pid,processes[i].arrT,processes[i].burstT,processes[i].waitT,processes[i].turnT);
    }
      printf("\n\nAverage Waiting Time:\t%f\n", wait_time/(float)p);
    printf("Average Turnaround Time:\t%f\n", turnaround_time/(float)p);
    
    return 0;
 }