#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BUFFER_SIZE 200

char dashLine[BUFFER_SIZE] = "---------------------------------------------------------------";

clock_t start, end;
double cpu_time_taken;

long long int getSumtoN(long long int n){
    long long int result = 0;
    start = clock();
    for (size_t i=1; i<=n; i++){
        result += i;
    }
    end = clock();
    cpu_time_taken = ((double)(end-start)) / CLOCKS_PER_SEC;
    return result;
}


int main (int argc, char *argv[]){
    printf("%s\n", dashLine);
    printf("Serial Method: \n");
    printf("Total sum from 1 to %d: %lld\n", atoi(argv[1]), getSumtoN(atoi(argv[1])));
    printf("Time taken to sum all the numbers %lf s\n", cpu_time_taken);
    return 0;
}