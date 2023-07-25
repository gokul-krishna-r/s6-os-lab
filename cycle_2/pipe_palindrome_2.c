#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main(){
    int fd2[2];
    if(pipe(fd2)==-1) printf("Error creating pipe");
    
    pid_t pid=fork();
    if(pid<0) printf("Error creating fork");
    
    if(pid==0){ //child
        close(fd2[1]);
        int len1;
        char str1[50];
        read(fd2[0],&str1,sizeof(str1));
        len1=strlen(str1);
        printf("String recieved from parent process: %d",len1);
        puts(str1);
        printf("\n");
        int i,j;
        
        char strr[len1];
        for(i=0; i<len1; i++){
            printf("Text: %c",str1[len1-i-1]);
            strr[i]=str1[len1-i-1];
            printf("Text: %c\n",strr[i]);
        }
        strr[i]='\0';
        puts(str1);
        puts(strr);
        if(strcmp(str1,strr)==0){
            printf("Palindrome");

        }else{
            printf("Not Palindrome");
        }
}
    else{
        char str2[50];
        close(fd2[0]);
        printf("Enter a string: ");
        scanf("%s",str2);
        write(fd2[1],str2,sizeof(str2));
        
    }
}