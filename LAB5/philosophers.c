#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h> 
#include <stdio.h>
#include <unistd.h>
#include <string.h>


// a set of defines for debugging purposes
#define NUMBER_OF_PHILOSOPHERS 5
#define EATING_TIME 4		// eating time
#define THINKING_TIME 5		// thinking time
#define INIT_TIME 2

int SEMA_KEY = -1;


void forkop(int left_fork_id, short sem_op);

void grab_forks(int left_fork_id) { return forkop(left_fork_id, -1); }

void put_away_forks(int left_fork_id) { return forkop(left_fork_id, 1); }

void forkop(int left_fork_id, short sem_op)
{//performing operations on the semaphores in the set indicated by semind.
  //structure:
  //sem_num - id of a semaphore
  //sem_op - operation (icrement, decrement)
  //sem_flag - operation flag
    int semcapacity = 2;
    struct sembuf op[semcapacity];

    op[0].sem_num = left_fork_id;
    op[1].sem_num = (left_fork_id + 1) % NUMBER_OF_PHILOSOPHERS;

    for(int counter = 0; counter < semcapacity; ++counter)
    {
        op[counter].sem_op = sem_op;
        op[counter].sem_flg = 0;
    }

    if (semop(SEMA_KEY, op, 2) == -1){
 printf("> \t\t %s_forks semop failed. \n", sem_op == -1 ? "grab" : "put_away");
}
        
}

int spawnphilosopher(int id)
{
printf("Start your dining\n");
    printf("Philosopher [%i]\t: process id: %i\n", id, getpid());
    sleep(INIT_TIME);
    int foods=0;
    for(int i = 0; i < 5; i ++)
    {
        printf("Philosopher [%i]\t: taking forks\n", id);
        grab_forks(id);

        printf("Philosopher [%i]\t: grabbed forks\t\t\t{Right Fork[%i]}-- :) --{Left fork[%i]}\n", id, id, (id + 1) % NUMBER_OF_PHILOSOPHERS);
        sleep(EATING_TIME);

        printf("Philosopher [%i]\t: putting away forks. He is done eating. He ate [%d] meals\n", id, ++foods);
        put_away_forks(id);

        printf("Philosopher [%i]\t: has put away forks\t\t{Right Fork[%i]}-- :) --{Left fork[%i]}\n", id, id, (id + 1) % NUMBER_OF_PHILOSOPHERS);
        sleep(THINKING_TIME);
    }
}

int main(int argc, const char * argv[])
{
  printf("\n");
    printf("%s\t\t: main process is running.\n", argv[0]);
    printf("Number of philosophers:\t %i\n", NUMBER_OF_PHILOSOPHERS);
    printf("Eating period:\t\t %is\n", EATING_TIME);
    printf("Thinking period:\t\t %is\n", THINKING_TIME);
    printf("Session starts in\t\t\t %is\n", INIT_TIME);
    printf("\n\n");

    // getting semaphore ID
    SEMA_KEY = semget(IPC_PRIVATE,NUMBER_OF_PHILOSOPHERS, 0600 | IPC_CREAT);//creating  a set of semaphores
    //semget(key_t key, int NumSem, int semflag)
    //IPC_PRIVATE - if this key value is set then we are creating  a new set of semaphores.
    //IPC_CREATE - used to create a new semaphore. Used with IPC_PRIVATE if there is no semaphore associated with the key
    //in success return the set identifier and if fail returns -1
    if (SEMA_KEY == -1)
    {
        printf("%s\t\t: semget failed", argv[0]);
        return 1;
    }

    // setting up semaphores
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i)
    {
      if (semctl(SEMA_KEY, i, SETVAL, 1) == -1)//performs the controll operations on the given semaphore set specified by key, or by a semaphore number.
	//SETVAL - sets a value to a semaphore
        {
            printf("%st\t: semctl failed", argv[0]);
            return 1;
        }
    }
    // spawning philosophers
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i)
    {
      pid_t new_pid = fork();//creating child processes(philosophers)
        if (new_pid == -1)
        {
            printf("%s\t\t: fork failed. Could not spawn a philosopher.", argv[0]);
            return 1;
        }

        if (new_pid == 0) 
            return spawnphilosopher(i);
    }

  


    return 0;
}
