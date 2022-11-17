#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY1 0x123
#define SHM_KEY2 0x124

#define NUM_MOVIES 1682
#define NUM_LINES 52000
#define BUFFER_SIZE 200
#define DELIM "\t"
#define FILE_NAME1 "./movie-100k_1.txt"
#define FILE_NAME2 "./movie-100k_2.txt"

char dashLine[BUFFER_SIZE] = "----------------------------------------------------------";

typedef struct{
    int userID;
    int movieID;
    int rate;
    int time;
} filmSurvey;

typedef struct{
    int counter[NUM_MOVIES];
    float avgPoint[NUM_MOVIES];
} ratingPoint;

void seperateStr(char *str, int *userID, int *movieID, int *rate, int *time){
    char *token = strtok(str, DELIM);
    *userID = atoi(token);
    token = strtok(NULL, DELIM);
    *movieID = atoi(token);
    token = strtok(NULL, DELIM);
    *rate = atoi(token);
    token = strtok(NULL, DELIM);
    *time = atoi(token);
}

void readFile(char *filename, filmSurvey *data, int *elementsNum){
    FILE *fptr = fopen(filename, "r");
    char line[BUFFER_SIZE] = "";
    int buffer[4] = {0, 0, 0, 0};
    while(fgets(line,sizeof(line),fptr)){
        seperateStr(line, &buffer[0], &buffer[1], &buffer[2], &buffer[3]);
        data[*elementsNum].userID = buffer[0];
        data[*elementsNum].movieID = buffer[1];
        data[*elementsNum].rate = buffer[2];
        data[*elementsNum].time = buffer[3];
        *elementsNum++;
    }
    fclose(fptr);
}

void calAvgRatingPoint(filmSurvey *data, int *counter, float *avgPoint, int *elementsNum){
    for (int i=0; i<*elementsNum; i++){
        counter[data[i].movieID] += 1;
        avgPoint[data[i].movieID] += data[i].rate;
    }

    for (int i=0; i<NUM_MOVIES; i++){
        if (counter[i] != 0){
            avgPoint[i] /= counter[i];
        }
    }
}

int main (int argc, char *argv[]){
    printf("%s\n", dashLine);

    char *filename1 = FILE_NAME1;
    char *filename2 = FILE_NAME2;

    filmSurvey data1[NUM_LINES];
    filmSurvey data2[NUM_LINES];

    int shmid1 = shmget(SHM_KEY1, sizeof(ratingPoint), 0644|IPC_CREAT);
    int shmid2 = shmget(SHM_KEY2, sizeof(int), 0644|IPC_CREAT);

    ratingPoint *storageSHM = (ratingPoint*)shmat(shmid1, 0, 0);
    int *elementsNum = (int*)shmat(shmid2, 0, 0);

    if (storageSHM == (ratingPoint*)-1){
        perror("shmat");
        exit(1);
    }
    else{
        for (int i=0; i<NUM_MOVIES; i++){
            storageSHM->counter[i] = 0;
            storageSHM->avgPoint[i] = 0;
        }
    }

    if (elementsNum == (int*)-1){
        perror("shmat");
        exit(1);
    }
    else *elementsNum = 0;
    
    pid_t pid1 = fork();
    pid_t pid2 = 1;

    if (pid1 == 0){ //child1 process
        readFile(filename1, &data1[0], elementsNum);
        calAvgRatingPoint(&data1[0], &(storageSHM->counter[0]), &(storageSHM->avgPoint[0]), elementsNum);
    }
    else{
        pid2 = fork();
        if (pid2 == 0){//child2 process
            readFile(filename2, &data2[0], elementsNum);
            calAvgRatingPoint(&data2[0], &(storageSHM->counter[0]), &(storageSHM->avgPoint[0]), elementsNum);
        }
        else{ //parent process
            for (int i = 1; i<=NUM_MOVIES; i++){
                if (storageSHM->counter[i] != 0){
                    printf("ID:%d   Average Point:%f   Counter:%d\n", i, storageSHM->avgPoint[i], storageSHM->counter[i]);
                }
            }
        }
    }

    // detach from the shared memory
    if (shmdt(storageSHM) == -1){
        perror("shmdt");
        return 1;
    }

    if (shmdt(elementsNum) == -1){
        perror("shmdt");
        return 1;
    }

    // mark the shared memory to be destroyed
    if (shmctl(shmid1, IPC_RMID, 0) == -1){
        perror("shmctl");
        return 1;
    }

    if (shmctl(shmid2, IPC_RMID, 0) == -1){
        perror("schmctl");
        return 1;
    }
    return 0;
}


