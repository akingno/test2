#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define NUMBER_OF_PROCESSES 4  

int main() {
    pid_t pid;
    int index;

    for (index = 0; index < NUMBER_OF_PROCESSES; ++index) {
        pid = fork();  

        if (pid < 0) {
            printf("Could not create process\n");  
            exit(1);
        } else if (pid == 0) {
            if (index == NUMBER_OF_PROCESSES - 1) {
                execl("/bin/ps", "ps", "ejH", 0);  
                printf("This code should not run\n");  
            } else {
                sleep(1);  
                printf("Hello from the %dth child process with PID %d\n", index, getpid());  
                exit(0);  
            }
        } else {
            printf("Hello from the parent process %d generating child %d\n", getpid(), pid);  
        }
    }

    return 0;
}
