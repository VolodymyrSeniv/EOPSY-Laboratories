#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopherID + N - 1) % N
#define RIGHT (philosopherID + 1) % N

pthread_mutex_t mutex;
pthread_mutex_t S[N];
int meals[N];
int philosophersArray[N] = {0, 1, 2, 3, 4};

int state[N];

void test(int philosopherID)
{
	if (state[philosopherID] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		// state that eating
		state[philosopherID] = EATING;
	++meals[philosopherID];
		printf("[Philosopher %d]: Eating\n", philosopherID);
		pthread_mutex_unlock(&S[philosopherID]);
	}
}

// take up chopsticks
void take_fork(int philosopherID)
{
    pthread_mutex_lock(&mutex);

	// state that hungry
	state[philosopherID] = HUNGRY;

	printf("[Philosopher [%d]: taking forks L [%d] and R [%d] \n", philosopherID, LEFT, RIGHT);

	// eat if neighbours are not eating
	test(philosopherID);

	pthread_mutex_unlock(&mutex);

	// if unable to eat wait to be signalled
	pthread_mutex_lock(&S[philosopherID]);

       
}

// put down chopsticks
void put_fork(int philosopherID)
{

	pthread_mutex_lock(&mutex);

	state[philosopherID] = THINKING;
	test(LEFT);
	test(RIGHT);


	printf("[Philosopher %d]: Put away forks.He ate [%d]\n", philosopherID, meals[philosopherID]);

	pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num)
{
  printf("I am here to eat \n");
  while(1){
		int* i = num;
		printf("Philosopher [%d]: Thinking \n", *i);
		sleep(3);

		take_fork(*i);
	       
		sleep(3);

		put_fork(*i);
  }
}

int main()
{
  for(int i = 0; i < N; i++){
    meals[i] = 0;
}
  
	pthread_t thread[N];

	// initialize the semaphores
	if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\n Initialization was failed\n");
        return 1;
    }

	// sem_init(&mutex, 0, 1);

	for (int i = 0; i < N; i++){

	  if (pthread_mutex_init(&S[i], NULL) != 0) {//initializing a mutex
			printf("\n Initialization of S[%d] was failed\n", i);
			return 1;
    	}
	}

	for (int i = 0; i < N; i++) {
		// create philosopher processes
	  pthread_create(&thread[i], NULL, (void*)&philosopher,(void*)&philosophersArray[i]);//creating a new phread

	}

	for (int i = 0; i < N; i++){
	  
	  pthread_join(thread[i], NULL);//waiting for a specific thread to be terminated
		pthread_mutex_destroy(&mutex);
	}
	for (int i = 0; i < N; i++){
		pthread_mutex_destroy(&S[i]);
	}
}
