#include<stdio.h>
#include<semaphore.h>
sem_t mutex,full,empty;
int main()
{
int value,mutexstatus,N,i;
printf("Buffer size:");
scanf("%d",&N);
sem_init(&mutex, 0, 1);
sem_getvalue(&mutex, &value);
printf("Semaphore mutex created with %d value:\n",value);
sem_init(&full, 0,  0);
sem_getvalue(&full, &value); 
printf("Semaphore full created with %d value:\n",value);
sem_init(&empty, 0, N);
sem_getvalue(&empty, &value); 
printf("Semaphore empty created with %d value:\n",value);
while(1)
{
    printf("\n1:produce\n2:consume\nSelect next action:");
    scanf("%d",&i);
    sem_getvalue(&empty, &value);
    sem_getvalue(&mutex, &mutexstatus);
    if(i==1 && value>0 && mutexstatus==1)
    {   
        sem_wait(&empty); 
        sem_wait(&mutex); 
        printf("producing\n");
        sem_post(&full);
        sem_post(&mutex);
    }
    else if(i==1)
    {
        printf("Buffer is full!!!\n");
        
    }
    
    sleep(1);
    
    sem_getvalue(&empty, &value);
    sem_getvalue(&mutex, &mutexstatus);
    if(i==2 && value<N && mutexstatus==1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        printf("consuming\n");
        sem_post(&empty);
        sem_post(&mutex);
        
    }
    else if(i==2)
    {
        printf("Buffer is empty!!!\n");
        
    }
    sem_getvalue(&full, &value);
    printf("Buffer status %d/%d\n",value,N);
    
}

}