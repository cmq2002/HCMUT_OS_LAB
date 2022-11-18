#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 200

static int pipefd1[2], pipefd2[2];

int returnStatus1, returnStatus2;

char pipe1WriteMessage[BUFFER_SIZE] = "Good day my child";

char pipe2WriteMessage[BUFFER_SIZE] = "Hello, how are u today ?";

char readMessage[BUFFER_SIZE];

char dashLine[BUFFER_SIZE] = "---------------------------------------------------------------";

void INIT(void){
    if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void WRITE_TO_PARENT(void){
   //send parent a message through pipe
   close(pipefd2[0]);
   printf("Child sends message to parent! -->> %s\n", pipe2WriteMessage);
   write(pipefd2[1], pipe2WriteMessage, sizeof(pipe2WriteMessage));
}

void READ_FROM_PARENT(void){
   //read a message sent by parent from pipe
   close(pipefd1[1]);
   read(pipefd1[0], readMessage, sizeof(readMessage));
   printf("Child receives message from parent! <<-- %s\n", readMessage);
}

void WRITE_TO_CHILD(void){
   //send child a message through pipe
   close(pipefd1[0]);
   printf("Parent sends message to child! -->> %s\n",pipe1WriteMessage);
   write(pipefd1[1], pipe1WriteMessage, sizeof(pipe1WriteMessage)); 
}

void READ_FROM_CHILD(void){
   //read a message sent by child from pipe
   close(pipefd2[1]);
   read(pipefd2[0], readMessage, sizeof(readMessage));
   printf("Parents receive message from child! <<-- %s\n", readMessage); 
}


int main (int argc, char* argv[]){
    printf("%s\n", dashLine);
    
    INIT();
    
    returnStatus1 = pipe(pipefd1);
    if (returnStatus1 == -1){
        printf("Unable to create pipe 1\n");
    }


    returnStatus2 = pipe(pipefd2);
    if (returnStatus2 == -1){
        printf("Unable to create pipe 2\n");
    }

    pid_t pid;
    pid = fork();
    //set a timer, process will end after 1 second
    // alarm(10);
    if (pid == 0){ //child process
        // while(1){
            // sleep(rand()%2+1);
            WRITE_TO_CHILD();
            READ_FROM_CHILD();
        // }
    }
    else{ //parent process
        // while(1){
            // sleep(rand()%2+1);
            READ_FROM_PARENT();
            WRITE_TO_PARENT();
        // }
    }
    return 0;
}