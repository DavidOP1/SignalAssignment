#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {
		case SIGCHLD:
			printf("I am in sighandler 1\n");
			alarm(2);
			for (int i = 1;; i++)
			{
				sleep(1);
			}
			fflush(stdout);
			break;
		case SIGALRM: 
			printf("I am in sighandler 2\n");
			fflush(stdout);
			k=i/j;
			printf("didnt get divison by 0\n");
			fflush(stdout);
			break;
		case SIGFPE:
			printf("I am in sighandler 3\n");
            char *temp="Hello";
            temp[5]='s';
			fflush(stdout);
            break;
        case SIGSEGV:
		 	printf("I am in sighandler 4\n");
            raise(SIGSYS);
		 	fflush(stdout);
            break;
        case SIGSYS:
			printf("I am in sighandler 5 \n");
            int currentPid=getpid();
            kill(currentPid,SIGTERM);
			fflush(stdout);
            break;
        case SIGTERM:
            printf("I am in sighandler 6 \n");
			fflush(stdout);
			abort();
			break;
		case SIGABRT:
		    printf("I am in sighandler 7\n");
			fflush(stdout);
            exit(1);
}
}

int main()
{
    system("exit");
	int status;
	signal (SIGCHLD, sig_handler);
	//signal (SIGUSR1, sig_handler);
	signal (SIGFPE, sig_handler);
    signal (SIGSEGV, sig_handler);
    signal (SIGSYS, sig_handler);
	signal (SIGTERM, sig_handler);
	signal (SIGABRT, sig_handler);
	signal(SIGALRM,sig_handler);
	if (!(fork())) {
		exit(1);
	}
	wait(&status);

}