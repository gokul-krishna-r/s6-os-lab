#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>


void revstr(char *str){
int temp;
int len=strlen(str);
for(int i=0;i<len/2;i++){
	temp=str[i];
	str[i]=str[len-i-1];
	str[len-i-1]=temp;
}
}

int main(){

int size_pipe_one[2],size_pipe_two[2],arr_pipe_one[2],arr_pipe_two[2];

pipe(size_pipe_one);
pipe(size_pipe_two);
pipe(arr_pipe_one);
pipe(arr_pipe_two);

int pid=fork();

if(pid==0){//child process
    close(size_pipe_one[1]);
    close(arr_pipe_one[1]);
    
    char buffer[10][10];
    int char_count=0;
    char rev_buffer[10][10];
    read(size_pipe_one[0],&char_count,sizeof(char_count));
    read(arr_pipe_one[0],&buffer,sizeof(buffer));
    int temp;
    for(int i=0;i<char_count;i++)
    {	
    	revstr(buffer[i]);
    }
    for(int i=0;i<char_count;i++){
    	for(int j=0;j<10;j++){
  
    		rev_buffer[i][j]=buffer[i][j];
    	}
    }
      for(int i=0;i<char_count;i++){
        puts(rev_buffer[i]);
    }
    
    
    
}else{ //parent process
    close(size_pipe_one[0]);
    close(arr_pipe_one[0]);
    close(arr_pipe_two[1]);
    close(size_pipe_two[1]);

    int char_count=0;
    char c='\0';
    char buffer[10][10];
    printf("Enter no of names:\n");
    scanf("%d",&char_count);

    printf("Enter name:\n");
    for(int i=0;i<char_count;i++){
    	scanf("%s",buffer[i]);
        printf("%d",strlen(buffer[i]));
    }

    write(size_pipe_one[1],&char_count,sizeof(char_count));
    write(arr_pipe_one[1],buffer,sizeof(buffer));


    wait(NULL);
}
return 0;
}