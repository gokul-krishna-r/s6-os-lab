#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<ctype.h>



int main(){

int arr_pipe_one[2];
int arr_pipe_two[2];

pipe(arr_pipe_two);
pipe(arr_pipe_one);

int pid=fork();

if(pid==0){//child process
    close(arr_pipe_one[1]);
    close(arr_pipe_two[0]);
    char buffer[10];
    int palindrome=1;
    read(arr_pipe_one[0],&buffer,sizeof(buffer));
    int len=strlen(buffer);
    for(int i=0;i<len/2;i++){
    	if(tolower(buffer[i])!=tolower(buffer[len-i-1])){
    		palindrome=0;
    		break;
    	}
    	palindrome=1;
    }
    write(arr_pipe_two[1],&palindrome,sizeof(palindrome));   
    
}else{ //parent process

    close(arr_pipe_one[0]);
    close(arr_pipe_two[1]);
    int palindrome=0;
   
    char buffer[10];
    printf("Enter string:\n");
    scanf("%s",buffer);

    write(arr_pipe_one[1],buffer,sizeof(buffer));
    read(arr_pipe_two[0],&palindrome,sizeof(palindrome));
    if(palindrome==1){
    	printf("The string is palindrome\n");
    }else{
    	printf("The string is not palindrome\n");
    }
    wait(NULL);
}
return 0;
}