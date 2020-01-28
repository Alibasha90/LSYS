#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
int c=5;
sem_t mutex1,mutex2;
void * fun1(void *);
void * fun2(void *);
void * fun3(void *);
void * fun4(void *);
int main()
{
	sem_init(&mutex1,0,1);
	sem_init(&mutex2,0,1);
	pthread_t th1,th2,th3,th4;
	if(pthread_create(&th1,NULL,fun1,NULL)<0)
	{
		perror("Thread1 fails...\n");
		return -1;
	}
	/*if(pthread_create(&th2,NULL,fun2,NULL)<0)
        {
                perror("Thread2 fails...\n");
                return -1;
        }*/
	if(pthread_create(&th3,NULL,fun3,NULL)<0)
        {
                perror("Thread3 fails...\n");
                return -1;
        }
	/*if(pthread_create(&th4,NULL,fun4,NULL)<0)
        {
                perror("Thread4 fails...\n");
                return -1;
        }*/
pthread_exit(NULL);
}

void * fun1(void * args)
{
	printf("Thread1..\n");
//	sem_wait(&mutex1);
	printf("Thread1 enter into critical section...\n");
	int i;
	for(i=1;i<=5;i++)
	{
		printf("Thread1_c:%d\n",c*i);
		//c++;
	}
	//sleep(5);
	for(i=6;i<=10;i++)
	{
		printf("Thread1_c:%d\n",c*i);
		//c++;
	}

	//sem_post(&mutex1);
	sem_wait(&mutex1);
}
void * fun2(void * args)
{
        printf("Thread2..\n");
        //sem_wait(&mutex2);
	sem_post(&mutex1);
        printf("Thread2 enter into critical section...\n");
	sleep(5);
        int i;
        for(i=0;i<10;i++)
        {
                printf("Thread2_c:%d\n",c);
                c++;
        }
	//sleep(5);
	//sem_post(&mutex2);
}
void * fun3(void * args)
{
        printf("Thread3..\n");
      // sem_wait(&mutex1);
	sem_post(&mutex1);
        printf("Thread3 enter into critical section...\n");
        int i;
        printf("value of. %d\n",c);
       // for(i=0;i<10;i++)
        {
         //       printf("Thread3_c:%d\n",c);
                c++;
        }
	//sleep(5);
//	sem_post(&mutex1);
}
void * fun4(void * args)
{
        printf("Thread4..\n");
       sem_wait(&mutex2);
        printf("Thread4 enter into critical section...\n");
        int i;
        for(i=0;i<10;i++)
        {
                printf("Thread4_c:%d\n",c);
                c++;
        }
	sleep(5);
	sem_post(&mutex2);
}

