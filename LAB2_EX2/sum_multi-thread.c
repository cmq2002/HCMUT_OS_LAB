#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX_THREADS 1000

long long int sum = 0;

long long int n = 0;

int numThreadsInput = 0;

typedef struct {
    int thread_id;
    long long int uppperBound;
    long long int lowerBound;
} thread_data;

thread_data arr[MAX_THREADS];

void *getSum(void *param){
    thread_data *my_data = (thread_data*) param;
    for (long long int i = my_data->lowerBound; i <= my_data->uppperBound; i++){
        sum += i;
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
    pthread_t tid[MAX_THREADS];
    pthread_attr_t attr;

    numThreadsInput = atoi(argv[1]);
    n = atoi(argv[2]);

    for (size_t i = 0; i < numThreadsInput; i++){
        arr[i].thread_id = i;
        arr[i].lowerBound = (i*n)/numThreadsInput + 1;
        arr[i].uppperBound = ((i+1)*n)/numThreadsInput;
        pthread_create(&tid[i], &attr, getSum, (void*)&arr[i]); 
    }

    for (size_t i = 0; i < numThreadsInput; i++){
        pthread_join(tid[i],NULL);
    }

    printf("Sum from 1 to %lld: %lld\n", n, sum);
    pthread_exit(EXIT_SUCCESS);
}
