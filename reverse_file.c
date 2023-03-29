#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main(){
    int n=0;
    printf("Enter no of lines: ");
    scanf("%d",&n);
    if(n<0){
        printf("Not valid no of lines\n");
        exit(0);
    }
    int fd1=open("source.txt",O_RDONLY);
    if(fd1==-1){
       printf("Error file does not exist");
        exit(0);    
    }
    char buffer[3];
    int fd2=open("target.txt",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP,S_IROTH);
    lseek(fd2,0,SEEK_SET);
    off_t fileLength=lseek(fd1,0,SEEK_END);
    int count=0;
    int new_line=0;
    
    while(count+fileLength>0){
        lseek(fd1,count-2,SEEK_END);
        read(fd1,buffer,1);
        if(buffer[0]=='\n'){
            new_line++;
        }
        if(new_line==n){
            break;
        }else{
            write(fd2,buffer,1);
        }
        count-=1;
    }
    printf("Completed");

}
