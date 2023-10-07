#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int checkLeapYear(int year){
	if((year%4==0 && year%100!=0) || year%400==0){
		return 1;
	}
	return 0;
}
int main(){

	int pid;
	int year_pipe[2],year_pipe_2[2];
	pipe(year_pipe);
	pipe(year_pipe_2);
	pid=fork();
	
	if(pid==0){
		close(year_pipe[1]);
		close(year_pipe_2[0]);
		int year;
		read(year_pipe[0],&year,sizeof(year));
		int result=checkLeapYear(year);
		write(year_pipe_2[1],&result,sizeof(result));
	
	}else{
		close(year_pipe[0]);
		close(year_pipe_2[1]);
		int year;
		printf("Enter the year: ");
		scanf("%d",&year);
		write(year_pipe[1],&year,sizeof(year));
		int isLeap=0;
		read(year_pipe_2[0],&isLeap,sizeof(isLeap));
		if(isLeap==1){
			printf("Year is Leap Year"); 
		}else{
			printf("Year is not Leap Year"); 			
		}
		wait(NULL);
	}
	
	return 0;

}