#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// try 1
int main(){
    pid_t id=fork();
    if (id==0) {
        printf("child printing: \n");
        for(int i=0; i<10; i++)
            printf("%d\n", i);
    } else {
        wait(NULL);
        printf("Parent resuming\n");
    }
    return 0;
}

// try 2
int main() {
    pid_t pid1 = fork();
    if (pid1==0) {
        printf("first proc: pid: %d, parentId: %d\n", getpid(), getppid());
        exit(0);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        printf("for 2nd: pid: %d, parentId: %d\n", getpid(), getppid());
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    return 0;
}

// try 3
int main() {
    pid_t id1=fork();
    if (id1==0) {
        pid_t id2=fork();
        if (id2 == 0) {
            pid_t id3 = fork();
            if (id3 == 0) {
                printf("pid: %d, parentID: %d\n", getpid(), getppid());
                exit(0);
            }
            printf("pid: %d, parentID: %d\n", getpid(), getppid());
            exit(0);
        }
        printf("pid: %d, parentID: %d\n", getpid(), getppid());
        exit(0);
    }
    return 0;
}

// try 4
int main() {
    pid_t id=fork();

    if (id == 0) {
        // Child process
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else if (id > 0) {
        // Parent process
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), id);
        wait(NULL); // Wait for child
    }
    return 0;
}

