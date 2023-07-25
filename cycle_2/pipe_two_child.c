#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){

int pipe_1[2],pipe_2[2],pipe_3[2];
int pid1,pid2;

pipe(pipe_1);
pipe(pipe_2);
pipe(pipe_3);

pid1=fork();
if(pid1==0){
	sleep(4);
	close(pipe_1[1]);
	close(pipe_2[0]);
	int num;
	read(pipe_1[0],&num,sizeof(num));
	num=num+5;
	write(pipe_2[1],&num,sizeof(num));

}else{
	pid2=fork();
	if(pid2==0){
		sleep(4);
		close(pipe_2[1]);
		close(pipe_3[0]);
		int num;
		read(pipe_2[0],&num,sizeof(num));
		num=num+5;
		write(pipe_3[1],&num,sizeof(num));
		
	}else{
	
	close(pipe_1[0]);
	close(pipe_3[1]);
	int num;
	int result;
	scanf("%d",&num);
	write(pipe_1[1],&num,sizeof(num));

	read(pipe_3[0],&result,sizeof(result));
	printf("%d",result);
	wait(NULL);
	}
}


return 0;
}