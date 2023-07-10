//*SENIV VOLODYMYR 309358 LAB2//

//pid_t - a data type to represent a process ID
//signal() - function to handle signal 
//SIGTERM - termination request set to program   
//getpid() - returns the id of the current process
//getppid() - returns the id of the parent process
//sleep()- makes a current thread to wait 
//kill()-function which sends the signal to a process or a process group specified by pid
//sigignore()- igring signal 
//SIGINT - the signal which is associated with the terminal interupt character  
//SIG_DFL - the signal which restores the defult service handlers
//SIGCHLD - when a child process stops or terminates this signal is sent to the aprent process

#include "stdio.h"
#include "signal.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"
#define WITH_SIGNALS

#define NUM_CHILD 10//creating 10 NUM_CHILD processes 
int keyboardFlag = 0;
#ifdef WITH_SIGNALS
void creatingSignal(int signum, void(*handler)(int)){
  struct sigaction newSigaction;//telling how we are going to handle a signal;
  newSigaction.sa_handler = handler;
  //newSigaction.sa_flags = SA_NODEFER;
  sigaction(signum, &newSigaction, NULL);
}

void customHandler(int signum){
  if(signum == SIGINT){//handler for parent
    printf("Parent - [%d]. Interrupt signal \n", getpid());
    keyboardFlag = 1;
}
  else if(signum == SIGTERM){//handler for child
    printf("Child - [%d]. Termination signal \n", getpid());
    keyboardFlag = 1;
}
  else {
    printf("Process ID - [%d]. Unknown signal [%d] \n", getpid(), signum);
}
}

#endif

void killFunction(pid_t* child, int size){
  int i;
  for(i = 0; i < size; i ++){//for each of the created process we send them the signal using kill() fucntion
    printf("Child - [%d] was terminated kill()\n", child[i]);
    kill(child[i],SIGTERM);

}


}

//Without signal handlers
int processing(){
  int i, j;
  int termination = 0;
  pid_t child[NUM_CHILD];
  for( i = 0; i < NUM_CHILD; i ++){
#ifdef WITH_SIGNALS
    if(keyboardFlag){ //checking the mark. Task 3. (4)
    printf("Parent - [%d]: \n", getpid());
    printf("Interruption mark is set. Signalling to all kreated processes \n");
    killFunction(child, i);
    break;
}
#endif
    child[i] = fork();//after creating a process, function fork() returns 0, if it was successfuly created, and negative if it is failed
    if(child[i] == 0){//checking wether the processes were created properly 
#ifdef WITH_SIGNALS
      creatingSignal(SIGINT,SIG_IGN);//ignoring signal
      creatingSignal(SIGTERM,customHandler);//own handler for child process
#endif
      printf("Child - [%d] was successfuly created. Parent - [%d] \n",getpid(),getppid());//process identifier 
      //signal(SIGINT, handler);
   
      sleep(15);
      exit(0);

    }
    else if(child[i] == -1){
      printf("Parent - [%d]: child [%d] was not created \n",getppid(),getpid());
      killFunction(child, i);//sending messages to all child processes
      exit(1);
    }
    sleep(1);//one second delay between fork() calls
  }
    printf("Parent - [%d]. Child processes have already been created \n",getpid());
    //waiting for the no need to synchronise child  processes with the paretn process 
    for(j = 0; j < NUM_CHILD; j ++){ 
      int status;
      if(waitpid(child[j], &status, 0) == -1){//when we are using this declaration it is the same as "wait()", but it is better to use when we want to check every process.
	perror("waitpid failed");
	return EXIT_FAILURE;
      }
      //getting the exit codes
 if ( WIFEXITED(status) ) {
   // int exitStatus = WEXITSTATUS(status);
	termination++;
        printf("Parent[%d]: Child[%d].Executions status is %d\n",getpid(), child[j], WEXITSTATUS(status));
    }
	}
    printf("////////////////////////////////////////////////////////////////// \n");
	printf("Number of terminations: %d \n",termination);
	printf("////////////////////////////////////////////////////////////////// \n");
	printf("Execution was completed\n");
		return 0;
    }



void main(int argc, char* argv[]){
  int i;
  printf("Signal handling is ");
#ifdef WITH_SIGNALS
  for(i = 0; i < NUM_CHILD; i ++ ){
    sigignore(i);
}
  creatingSignal(SIGINT,customHandler);//setting own interrupt signal handler
  creatingSignal(SIGCHLD, SIG_DFL);//restore the default handler for SIGCHLD signal
  printf("ON\n");
#else
  printf("OFF\n");
#endif
//signal(SIGINT, handler);
  printf("Parent[%d] \n", getpid());
  processing();
#ifdef WITH_SIGNALS //restoring the old service handlers of all signals 
   for(i = 0; i < _NSIG; i ++){
    signal(i, SIG_DFL);
}
#endif
}
