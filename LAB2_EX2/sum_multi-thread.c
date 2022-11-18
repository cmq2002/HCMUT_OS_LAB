#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 1000
#define BUFFER_SIZE 200

char dashLine[BUFFER_SIZE] = "---------------------------------------------------------------";

static long long int totalSum = 0;

typedef struct {
    long long int uppperBound;
    long long int lowerBound;
} thread_data;

thread_data arr[MAX_THREADS];

void *getSum(void *param){
    thread_data *my_data = (thread_data*) param;
    long long int segSum = 0;
    for (long long int i = my_data->lowerBound; i <= my_data->uppperBound; i++){
        segSum += i;
    }
    totalSum += segSum;
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
    printf("%s\n", dashLine);

    pthread_t tid[MAX_THREADS];
    pthread_attr_t attr;

    int numThreadsInput = atoi(argv[1]);
    long long int n = atoi(argv[2]);

    clock_t start, end;
    double cpu_time_taken;

    start = clock();

    for (size_t i = 0; i < numThreadsInput; i++){
        arr[i].lowerBound = (i*n)/numThreadsInput + 1;
        arr[i].uppperBound = ((i+1)*n)/numThreadsInput;
        pthread_create(&tid[i], &attr, getSum, (void*)&arr[i]); 
    }

    for (size_t i = 0; i < numThreadsInput; i++){
        pthread_join(tid[i],NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end-start)) / CLOCKS_PER_SEC;

    printf("Multi-thread method: \n");
    printf("Total sum from 1 to %lld: %lld\n", n, totalSum);
    printf("Time taken to sum all the numbers %lf s\n", cpu_time_taken);
    pthread_exit(EXIT_SUCCESS);
}
