#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// example of wait function
int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process (PID %d) running...\n", getpid());
        sleep(2);
        printf("Child done.\n");
    } else if (pid > 0) {
        // Parent process
        printf("Parent waiting for child to finish...\n");
        wait(NULL);  // Block here until child finishes
        printf("Child finished. Parent resumes.\n");
    }
    return 0;
}
/* int main() { */
/*     pid_t id=fork(); */
/*     pid_t tt = wait(NULL); */
/*     if (tt==0) */
        /* printf("hello world: %d\n", tt); */
    /* pid_t tt = wait(NULL); */
    /* int id=fork(); */

    /* printf("hello world: %d\n", tt); */
    /* return 0; */
/* } */

/* int main() { */
/*     int id=fork(); */
/*     if (id == 0){ */
/*         sleep(2); */
/*     } */
/*     printf("currID: %d, parID: %d\n", getpid(), getppid()); */

/*     int response = wait(NULL); */

/*     if (response == -1) */
/*         printf("no child process to finish\n"); */
/*     else */
/*         printf("%d finished its execution\n", response); */

/*     return 0; */
/* } */
