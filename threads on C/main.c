#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t p1;//consumer
pthread_t p2;//consumer
pthread_t p3;//  producer
pthread_t p4;//consumer
pthread_t p5;//  producer

int MAX_STACK_LENGHT = 20;

typedef struct S_stack {
    int *data;
    int head;//и вершина, и размер.
} STACK;
STACK	stack;
pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;
sem_t	SCR1;
sem_t	SP2;
sem_t	SP5;

void push(){
	if(stack.head < MAX_STACK_LENGHT){
		stack.head++;
		stack.data[stack.head] = stack.head*3;
		printf(" %d\n",stack.head);
	}
}

int pop(){
	if(stack.head > 0){
	return stack.head;
	stack.head--;
	}
}

void* thread_producer(void* sem)
{
    int p_num = *(int*)sem;
    int sem_value;

    while (1) {
        if (stack.head == -1)
            break;

        if(p_num == 2){
    		sem_post(&SP5);
    		sem_wait(&SP2);
    	}
    	else if (p_num == 5){
    		sem_post(&SP2);
    		sem_wait(&SP5);
    	}

        sem_getvalue(&SCR1,&sem_value);

        if (sem_value < MAX_STACK_LENGHT){
            pthread_mutex_lock (&MCR1);
            push();
            sem_getvalue(&SCR1,&sem_value);
            printf("Producer thread%d: semaphore=%d; element %d CREATED; \n",p_num,sem_value,stack.head);
            pthread_mutex_unlock (&MCR1);
            sem_post (&SCR1);
        }
        sem_wait(&SP2);
        sem_wait(&SP5);
    }
    printf("Producer thread%d  stopped\n",p_num);
    pthread_cancel(p1);
    pthread_cancel(p2);
    pthread_cancel(p2);
    pthread_cancel(p4);
    pthread_cancel(p5);

    return NULL;
}


void* thread_consumer (void* sem)
{
    int p_num = *(int*)sem;
    int sem_value;

    while (1)
    {
        if (sem_trywait (&SCR1) == 0 )
        {
            pthread_mutex_lock (&MCR1);
          
            sem_getvalue(&SCR1,&sem_value);
            printf("Consumer thread%d: semaphore=%d; element %d TAKEN; \n",p_num,sem_value,pop());
            pthread_mutex_unlock (&MCR1);
        }
        else
            printf("Consumer thread%d does some useful work\n",p_num);
        if (sem_value == 0)
            		break;
    }

    printf("Consumer thread%d  stopped\n",p_num);

    return NULL;
}


int main()
{
	stack.head= -1;
	stack.data = malloc(MAX_STACK_LENGHT*sizeof(int));
    sem_init (&SCR1, 0, 0);
    sem_init (&SP2, 0, 1);
    sem_init (&SP5, 0, 1);

    printf ("Max lenght of stack is: %d\n",MAX_STACK_LENGHT);
    int sem_value;
    sem_getvalue(&SCR1,&sem_value);
    printf("semaphore=%d\n",sem_value);

    int length_at_start=13;
    int i;

    for(i=0; i < length_at_start; ++i)
    {
        push();
        sem_post(&SCR1);
    }
    printf("Stack with %d-th(0-%d) elements has been created\n",length_at_start,length_at_start-1);
    sem_getvalue(&SCR1,&sem_value);
    printf("semaphore=%d\n",sem_value);

    int p1_number=1;
    int p2_number=2;
    int p3_number=3;
    int p4_number=4;
    int p5_number=5;

    pthread_create (&p1,NULL,&thread_consumer,(void*)&p1_number);
    pthread_create (&p2,NULL,&thread_consumer,(void*)&p2_number);
    pthread_create (&p2,NULL,&thread_producer,(void*)&p3_number);
    pthread_create (&p4,NULL,&thread_consumer,(void*)&p4_number);
    pthread_create (&p5,NULL,&thread_producer,(void*)&p5_number);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
    pthread_join(p5,NULL);

    printf("All threads stopped\n");

    return 0;
}
