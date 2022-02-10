#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAXARGS 20
#define ARGLEN 100

void execute(char *arglist[]);
int main()
{
	char *arglist[MAXARGS + 1];
	char *history[MAXARGS + 1] = {'\0'};
	int numargs;
	char argbuf[ARGLEN];
	char *makestring();
	int count = 0;
	
	numargs = 0;
	
	while (numargs < MAXARGS)
	{
		printf("Arg[%d]? ", numargs);
		if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
			arglist[numargs++] = makestring(argbuf);
		else
		{

			if (numargs > 0)
			{
				
				arglist[numargs] = NULL;
				
				if(strcmp(*arglist,"!!")==0){
					if(count<1){
						printf("No commands in history\n");
						numargs = 0;
						continue;
					}
					printf("history: %s\n",*history);
					execute(history);
				}
				else{
					execute(arglist);
				}
				if(strcmp(*arglist,"!!")!=0){
					*history = *arglist;
				}
				numargs = 0;
				count++;
			}
		}
	}
	return 0;
}
void execute(char *arglist[])
{
	int pid, exitstatus;
	pid = fork();
	switch (pid)
	{
	case -1:
		perror("fork failed");
		exit(1);
	case 0:
		execvp(arglist[0], arglist);
		perror("execvp failed");
		exit(1);
	default:
		while (wait(&exitstatus) != pid)
			;
		printf("child exited with status %d,%d\n", exitstatus >> 8, exitstatus & 0377);
	}
}
char *makestring(char *buf)
{
	buf[strlen(buf) - 1] = '\0';
	void *const cp = malloc(strlen(buf) + 1);
	if (cp == NULL)
	{
		fprintf(stderr, "no memory\n");
		exit(1);
	}
	strcpy(cp, buf);
	return cp;
}
