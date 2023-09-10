#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>


int main(){
	
	int arr_pipe[2],arr_pipe_2[2];
	int sum=0;
	int pid;
	pipe(arr_pipe);
	pipe(arr_pipe_2);
	pid=fork();
	int cur_date[3]={11,9,2023};
	
	
	
	if(pid==0){
		close(arr_pipe[1]);
		close(arr_pipe_2[0]);
		int age[3];
		int date_arr[3];
		read(arr_pipe[0],&date_arr,sizeof(date_arr));
		if(cur_date[0]<date_arr[0]){
			cur_date[0]+=30;
			cur_date[1]-=1;
		}
		if(cur_date[1]<date_arr[1]){
			cur_date[1]+=12;
			cur_date[2]-=1;
		}
		
		age[0]=cur_date[0]-date_arr[0];
		age[1]=cur_date[1]-date_arr[1];
		age[2]=cur_date[2]-date_arr[2];
		
		write(arr_pipe_2[1],age,sizeof(age));
		
	
	}else{
		close(arr_pipe[0]);
		close(arr_pipe_2[1]);
		int date[3];
		int age[3];
		printf("Enter DOB in dd mm yyyy: \n");
		scanf("%d%d%d",&date[0],&date[1],&date[2]);
		write(arr_pipe[1],date,sizeof(date));
		
		read(arr_pipe_2[0],&age,sizeof(age));
		printf("The age is : %d Years %d Months %d Days\n",age[2],age[1],age[0]);
		
		wait(NULL);
	}
	return 0;
}