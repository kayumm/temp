
//sjf

#include <stdio.h>

int main() {
    int at[4] = {0, 1, 2, 3};
    int bt[4] = {5, 3, 8, 6};
    int completed[4] = {0};
    int tat[4], wt[4];
    int time = 0, done = 0;
    int total_tat = 0, total_wt = 0;

    while (done < 4) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < 4; i++) {
            if (!completed[i] && at[i] <= time && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx != -1) {
            time += bt[idx];
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            done++;
        } else {
            time++;
        }
    }

    printf("ID\tTAT\tWT\n");
    for (int i = 0; i < 4; i++) {
        printf("P%d\t%d\t%d\n", i+1, tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("Total Turnaround Time = %d\n", total_tat);
    printf("Total Waiting Time = %d\n", total_wt);
    printf("Average Turnaround Time = %.2f\n", total_tat / 4.0);
    printf("Average Waiting Time = %.2f\n", total_wt / 4.0);
    return 0;
}



//priority 

#include <stdio.h>

int main() {
    int at[4] = {0, 1, 2, 3};
    int bt[4] = {5, 3, 8, 6};
    int pr[4] = {8, 1, 16, 5};
    int completed[4] = {0};
    int tat[4], wt[4];
    int time = 0, done = 0;
    int total_tat = 0, total_wt = 0;

    while (done < 4) {
        int idx = -1, min_pr = 9999;
        for (int i = 0; i < 4; i++) {
            if (!completed[i] && at[i] <= time && pr[i] < min_pr) {
                min_pr = pr[i];
                idx = i;
            }
        }

        if (idx != -1) {
            time += bt[idx];
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            done++;
        } else {
            time++;
        }
    }

    printf("ID\tTAT\tWT\n");
    for (int i = 0; i < 4; i++) {
        printf("P%d\t%d\t%d\n", i+1, tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("Total Turnaround Time = %d\n", total_tat);
    printf("Total Waiting Time = %d\n", total_wt);
    printf("Average Turnaround Time = %.2f\n", total_tat / 4.0);
    printf("Average Waiting Time = %.2f\n", total_wt / 4.0);
    return 0;
}



//shell scripting 


arr=(9 5 2 8 3)

echo "Original Array: ${arr[*]}"


asc=($(for i in "${arr[@]}"; do echo $i; done | sort -n))
echo "Ascending Order: ${asc[*]}"


desc=($(for i in "${arr[@]}"; do echo $i; done | sort -nr))
echo "Descending Order: ${desc[*]}"

//system call

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        // First child: sum 1 to 100
        int sum = 0;
        for (int i = 1; i <= 100; i++)
            sum += i;
        printf("Child 1 (PID: %d): Sum = %d, Parent PID: %d\n", getpid(), sum, getppid());
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            // Second child: factorial of 5
            int fact = 1;
            for (int i = 1; i <= 5; i++)
                fact *= i;
            printf("Child 2 (PID: %d): Factorial of 5 = %d, Parent PID: %d\n", getpid(), fact, getppid());
        } else {
            // Parent waits
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

