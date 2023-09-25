#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main() {
  pid_t pid;
  int NUMBER_OF_PROCESSES = 3;
  for(int i = 1;i< NUMBER_OF_PROCESSES;i++){
		pid = fork();
		if(pid < 0) {
			printf("Could not create process\n");
			exit(1);
		} else if(pid == 0){
			sleep(1);
		 
			printf("Hello from the %dth child process with PID %d\n",i,getpid());
			exit(0);
		}else if(pid > 0) {
		  //pid_parent = pid;
		printf("Hello from the %dth parent process %d generating child %d\n",i,getpid(),pid);
	        
		}
			
	}
  
  return 0;



 
	//printf("This code will be executed by both the child and parent\n");
}


