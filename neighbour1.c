#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;
pid_t *shmptr;
void __gcov_flush(void);

void sig1_handler(volatile sig_atomic_t usr_sig)
{
	signal(usr_sig, SIG_IGN);
	printf("Received instructions %u\nDumping neighbour's fight logs.\n I am happy you erred\n",usr_sig);
	__gcov_flush();
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(1);
}

void sig2_handler(volatile sig_atomic_t usr_sig)
{
	signal(usr_sig, SIG_IGN);
	printf("Received instructions %u\nDumping neighbour's complaints logs.\n I am kidnapped.\n",usr_sig);
	__gcov_flush();
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(2);
}

void sig3_handler(volatile sig_atomic_t usr_sig)
{
	signal(usr_sig, SIG_IGN);
	printf("Received instructions %u\nDumping neighbour's quarrel logs.\n I am killed\n",usr_sig);
	__gcov_flush();
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(3);
}

void sig4_handler(volatile sig_atomic_t usr_sig)
{
	signal(usr_sig, SIG_IGN);
	printf("Received instruction %u\ndumping error logs.\n I am spared\n",usr_sig);
	__gcov_flush();
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(4);
}

void main(int argc, char **argv[])
{
	int i;
	pid_t pid=getpid();
	key_t keygen;

	if (signal(SIGUSR1, sig1_handler)==SIG_ERR){
		printf("Error1. interrupt and try again\n");
		//signal(SIGINT, sigdf_handler);
		exit(0);
	}
	if (signal(SIGINT, sig2_handler)==SIG_ERR){
		printf("Error2. interrupt and try again\n");
		//signal(SIGINT, sigdf_handler);
		exit(0);
	}
	if (signal(SIGQUIT, sig3_handler)==SIG_ERR){
		printf("Error3. interrupt and try again\n");
		//signal(SIGINT, sigdf_handler);
		exit(0);
	}
	if (signal(SIGUSR2, sig4_handler)==SIG_ERR){
		printf("Error4. interrupt and try again\n");
		//signal(SIGINT, sigdf_handler);
		exit(0);
	}
	
	keygen=ftok(".",'s');
	shmid=shmget(keygen, sizeof(pid_t), IPC_CREAT | 0666);
	shmptr=(pid_t *) shmat(shmid, NULL, 0);
	*shmptr=pid;
	for(i=0; ;i++){
		printf("I am Neighbour %d:%dI like to annoy you\n",pid,i);
		sleep(2);}
	//signal(SIGINT, sigdf_handler);
}

