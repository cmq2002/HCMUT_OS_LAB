#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int getSumtoN(long long int n){
    long long int result = 0;
    for (size_t i=1; i<=n; i++){
        result += i;
    }
    return result;
}


int main (int argc, char *argv[]){
    printf("Sum from 1 to %d: %lld\n", atoi(argv[1]), getSumtoN(atoi(argv[1])));
    return 0;
}