#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void main(){
	int fd1,fd2;
	char buffer;
    char source[30],dest[30];

    printf("Enter source file name: ");
    scanf("%s",source);    

    fd1=open(source,O_RDONLY);
	if(fd1==-1){
		printf("Error file does not exist\n");
		exit(0);
	}
    while(1){
        printf("Enter destination file name: ");
        scanf("%s",dest);
	    fd2=open(dest,O_WRONLY|O_EXCL|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP,S_IROTH);
        if(fd2==-1){
            printf("File already exists\n");       
        }else{
            break;
        }
    }
 
	while(read(fd1,&buffer,1)){
		write(fd2,&buffer,1);
	}
	printf("Copied Successfully\n");
	close(fd1);
	close(fd2);
}
