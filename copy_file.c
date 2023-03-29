#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void main(){
	int fd1,fd2;
	char buffer;
	fd1=open("first.txt",O_RDONLY);
	if(fd1==-1){
		printf("Error file does not exist\n");
		exit(0);
	}
	fd2=open("target.txt",O_WRONLY|O_EXCL|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP,S_IROTH);
    if(fd2==-1){
        printf("File already exists\n");
        exit(0); 
    }
	while(read(fd1,&buffer,1)){
		write(fd2,&buffer,1);
	}
	printf("Copied Successfully\n");
	close(fd1);
	close(fd2);
}
