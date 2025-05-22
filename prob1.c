#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// slide 1 problem 2
int main() {
    int arr[5] = {0};
    int n = 0;

    printf("Enter integers (up to 5), use $ to stop:\n");
    
    while (n < 5) {
        char buffer[10];
        scanf("%s", buffer);

        if (buffer[0] == '$')
            break;

        arr[n] = atoi(buffer); // convert string to int
        n++;
    }

    pid_t pid1 = fork();

    if (pid1 == 0) {
        // Child 1 - sum
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += arr[i];
        printf("Sum: %d\n", sum);
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        // Child 2 - average
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += arr[i];
        float avg = (float)sum / n;
        printf("Average: %.2f\n", avg);
        exit(0);
    }

    pid_t pid3 = fork();

    if (pid3 == 0) {
        // Child 3 - max
        int max = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > max)
                max = arr[i];
        printf("Max: %d\n", max);
        exit(0);
    }

    // Parent waits for all children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
