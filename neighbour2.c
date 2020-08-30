#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct point {
   double x, y;
};
struct vector {
    int n;
    struct point *p;
};
struct tree {
    struct tree *left, *right;
    int key;
    struct vector *vector;
};

struct tree * maketree(int key)
{
	struct tree * tree = (struct tree*)malloc(sizeof(struct tree));
	tree->key=key;
	tree->left=NULL;
	tree->right=NULL;
	return tree;
}

struct tree * find (struct tree *tree, int key)
{
    if (! tree)
    return 0;

    if (key < tree->key)
    return find (tree->left, key);
    else if (key > tree->key)
    return find (tree->right, key);
    else if(key == tree->key)
    return key;
    //else return 0;
}

void main(int argc, char **argv[])
{
	pid_t pid;
	key_t keygen;
	int shmid;
	pid_t *shmptr;
	int i,randt;

	struct tree* randv=maketree(2);
	randv->left=maketree(1);
	randv->right=maketree(3);

	printf("Neighbour is annoying. Kidnap him(1) or kill him(2) or let him go(3)?\n");
	scanf("%d",&randt);

	keygen= ftok(".",'s');
	shmid=shmget(keygen, sizeof(pid_t), 0666);
	shmptr=(pid_t*)shmat(shmid, NULL, 0);
	pid=*shmptr;
	shmdt(shmptr);

	while(1){
		i=find(randv, randt);
		sleep(10);
		if(i==0){
			kill(pid, SIGUSR1);
			printf("Sent SIGUSR1 signal to neighbour. Wrong input. Neighbour %d is avenged\n",pid);
			exit(0);
		}
		else{
			if(i==1){
			kill(pid, SIGINT);            
                        printf("Sent SIGINT signal to neighbour. Neighbour %d is kidnapped\n",pid);
                        exit(0);
			}
			if(i==2){
			kill(pid, SIGQUIT);           
			printf("Sent SIGKILL signal to neighbour. Neighbour %d is killed\n", pid);
 			exit(0);
			}
			if(i==3){
			kill(pid,SIGUSR2);
			printf("Sent SIGUSR2 signal to neighbour. Neighbour %d is spared\n",pid);
			exit(0);
			}
		}
	}
}

