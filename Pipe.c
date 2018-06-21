#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(){

	int fd1[2];
	int fd2[2];
	char *fixed = "Harsh";
	char input[20];
	int p;
	if(pipe(fd1)==-1){
		printf("Pipe creation failed");
		return 1;
	}
	if (pipe(fd2)==-1){
		printf("pipe creation failed");
		return 1;
	}
	printf("Enter the string: ");
	scanf("%s",input);
	p = fork();
	if(p<0){
		perror("fork failed");
		return 1;
	}
	else if (p>0){		
		char concat[20];
		close(fd1[0]);
		write(fd1[1],input,strlen(input)+1);
		close(fd1[1]);
		wait(NULL);
		close(fd2[1]);
		read(fd2[0],concat,20);
		printf("String is: %s\n",concat);
		close(fd2[0]);
	}
	else{
		close(fd1[1]);
		char concat[20];
		read(fd1[0],concat,20);
		strcat(concat,fixed);
		close(fd1[0]);
		close(fd2[0]);
		write(fd2[1],concat,strlen(concat)+1);
		close(fd2[1]);
		exit(0);
	}
	return 0;
}
