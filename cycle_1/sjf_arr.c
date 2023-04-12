#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int getMinArr(int A[], int n)
{
    int smallest = A[0];
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (A[i] < smallest)
        {
            smallest = A[i];
            index = i;
        }
    }
    return index;
}

int main()
{
    int ArrT[20],BurstT[20];
    int NewBursT[20],NewArrT[20];
    int WaitT[20],TurnT[20];
    int p,range;
    int pid[20];
    int fid[20];
    int completionTime=0;

    WaitT[0]=0; //Waiting time of initial process is 0

    printf("Enter number of processes required: ");
    scanf("%d",&p);
    
    printf("Enter Burst and Arrival Time of processes:\n  Burst Time\tArrival Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d: " ,i+1);
        scanf("%d%d",&BurstT[i],&ArrT[i]);
        pid[i]=i;
    }

    for(int i=0;i<p;i++){
        for(int j=0;j<p-i-1;j++){
            if(ArrT[j]>ArrT[j+1]){
                int temp=BurstT[j];
                BurstT[j]=BurstT[j+1];
                BurstT[j+1]=temp;
                temp=ArrT[j];
                ArrT[j]=ArrT[j+1];
                ArrT[j+1]=temp;
                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
            }
        }
    }
    range=0;
    while(ArrT[range]==ArrT[0]){
        range++;    
        printf("%d\n",range);
    }

    int smallest=getMinArr(BurstT,range);
    printf("%d\n",smallest); 
    //Calculating TurnAround Time
    NewBursT[0]=BurstT[smallest];
    NewArrT[0]=ArrT[smallest];
    //getting count
    int i=1;
    range=0;
    while(range<p){
        range=0;
        completionTime=BurstT[smallest];
        for(range=0;ArrT[range]<completionTime;range++);
        smallest=getMinArr(BurstT,range);
        printf("%d\n",smallest); 
        NewBursT[i]=BurstT[smallest];
        NewArrT[i]=ArrT[smallest];
        i++;
    }
    
   
   
       //Calculating TurnAround Time
    completionTime=0;
    for(int i=1;i<p;i++){
        completionTime+=NewBursT[i];
        TurnT[i]=completionTime-NewArrT[i];
    }
    //Calculating Waiting Time
    for(int i=1;i<p;i++){
        WaitT[i]=TurnT[i]-NewBursT[i];
    }

     printf("Si No:\tArrival Time\tBurst Time\tWaiting time\tTurnAround Time\n");
    
    for(int i=0;i<p;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",pid[i]+1,NewArrT[i],NewBursT[i],WaitT[i],TurnT[i]);  
    }
    return 0;
}
