#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h> 

#define MAX_CUSTOMERS 100
#define MAX_TABLES 20

int red_count = 0;
int blue_count = 0;
int total_tables = 0;
int bakery_capacity = 0;
sem_t table_sem;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_equal = PTHREAD_COND_INITIALIZER;

typedef struct {
    int id;
    char color[6]; // "red" or "blue"
} Customer;

void get_string_input(const char* prompt, char* buffer, size_t size) 
{
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t ln = strlen(buffer) - 1;
        if (ln<size && buffer[ln] == '\n') buffer[ln]='\0';
    }
}

int get_int_input(const char* prompt, int min, int max) 
{
    char buffer[32];
    int value;
    int valid;
    do {
        valid = 1;
        get_string_input(prompt, buffer, sizeof(buffer));
        for (size_t i=0; buffer[i]!='\0'; i++)
            if (!isdigit(buffer[i])) {
                valid = 0;
                break;
            }
        if(!valid){
             printf("Invalid input! Please enter a number.\n");
             continue;
        }
        value = atoi(buffer);
        if (value <min || value > max) {
            printf("Invalid input! Please enter a number between %d and %d.\n", min, max);
            valid = 0;
        }
    } while (!valid);
    return value;
}

void get_color_input(char* color) 
{
    while (1) {
        get_string_input("  Enter outfit color (red/blue): ", color, 8);
        for (int i = 0; color[i]; i++) color[i] = tolower(color[i]);
        if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0) break;
        printf("  Invalid color! Please enter 'red' or 'blue'.\n");
    }
}

void* customer_routine(void* arg) {
    Customer* cust = (Customer*)arg;
    pthread_mutex_lock(&count_mutex);

    printf("[Queue] %s customer %d arrived, waiting to enter.\n",
           cust->color,cust->id);

    while (1) 
    {
        int current_inside = red_count + blue_count;
        int can_enter = 0;

        if (current_inside < bakery_capacity) 
        {
            if (strcmp(cust->color, "red") == 0) {
                if (red_count <= blue_count) {
                    can_enter = 1;
                }
            } else {
                if (blue_count <= red_count) {
                     can_enter = 1;
                }
            }
        }

        if (can_enter) break;
        printf("[Wait ] %s customer %d waiting outside (Red: %d, Blue: %d, Inside: %d/%d capacity).\n",
               cust->color, cust->id, red_count, blue_count, current_inside, bakery_capacity);
        pthread_cond_wait(&cond_equal, &count_mutex);
    }
    if (strcmp(cust->color, "red") == 0) red_count++;
    else blue_count++;
    int current_inside_after_entry = red_count + blue_count;

    printf("[Enter] %s customer %d ENTERED bakery. (Red: %d, Blue: %d, Inside: %d/%d capacity).\n",
           cust->color, cust->id, red_count, blue_count, current_inside_after_entry, bakery_capacity);

    pthread_mutex_unlock(&count_mutex);

    // printf("[Inside] %s customer %d is inside, waiting for a table.\n", cust->color, cust->id); // Reduced print

    sem_wait(&table_sem);

    /* printf("[Seat ] %s customer %d found a table and is eating.\n", cust->color, cust->id); */
    int eating_time = rand() % 3 + 1;
    sleep(eating_time);

    printf("[Leave] %s customer %d finished eating, leaving table (%d sec).\n", cust->color, cust->id, eating_time);
    sem_post(&table_sem);

    pthread_mutex_lock(&count_mutex);

    if (strcmp(cust->color, "red") == 0) red_count--;
    else blue_count--;
    int current_inside_after_leaving = red_count + blue_count;

    printf("[Exit ] %s customer %d LEFT bakery. (Red: %d, Blue: %d, Inside: %d/%d capacity).\n",
           cust->color, cust->id, red_count, blue_count, current_inside_after_leaving, bakery_capacity);

    pthread_cond_broadcast(&cond_equal);
    pthread_mutex_unlock(&count_mutex);
    free(cust);
    pthread_exit(NULL);
}

int main() 
{
    srand(time(NULL)); 
    printf("\n=== Sweet Harmony Bakery Simulation ===\n");

    total_tables = get_int_input("Enter the number of tables in the bakery (1-20): ", 1, MAX_TABLES);
    bakery_capacity = total_tables * 2; 
    int n_customers = get_int_input("Enter the total number of customers arriving (1-100): ", 1, MAX_CUSTOMERS);

    Customer* customer_data[n_customers];
    pthread_t threads[n_customers];

    printf("Enter outfit color for each customer:\n");
    for (int i = 0; i<n_customers; i++) 
    {
        char color[8];
        printf("Customer %d:\n", i + 1);
        get_color_input(color);

        customer_data[i] = malloc(sizeof(Customer));
        if (customer_data[i] == NULL) 
        {
            perror("Failed to allocate memory for customer data");
            for(int j = 0; j < i; ++j) free(customer_data[j]);
            return 1;
        }
        customer_data[i]->id = i + 1;
        strcpy(customer_data[i]->color, color);
    }
    if (sem_init(&table_sem, 0, total_tables) != 0) 
    {
        perror("Semaphore initialization failed");
        for(int i = 0; i < n_customers; ++i) free(customer_data[i]);
        return 1;
    }

    printf("\n--- Starting Customer Arrivals (Bakery Capacity: %d, Tables: %d) ---\n", bakery_capacity, total_tables);
    for (int i = 0; i < n_customers; i++) 
    {
        if (pthread_create(&threads[i], NULL, customer_routine, customer_data[i]) != 0) 
        {
             perror("Failed to create thread");
             sem_destroy(&table_sem);
             pthread_mutex_destroy(&count_mutex);
             pthread_cond_destroy(&cond_equal);
             for(int j = 0; j < i; ++j) free(customer_data[j]);
             exit(1);
        }
        usleep(100000 + rand()%300000);
    }

    for (int i = 0; i < n_customers; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&table_sem);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&cond_equal);
    printf("\n=== Simulation Complete! All customers have visited Sweet Harmony. ===\n");
    return 0;
}
