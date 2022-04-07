// Semephore used to implement solution for the producer consumer problem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mutex = 1;
// full > 0 then only consumer can consume
int full = 0;
int empty =5,x = 0;
void producer()
{
    // initially,mutex = 1, so producer can acquires the lock(critical section is free)
    // then mutex decrease to zero now the critical section is not free because the producer already acquired the lock.
    mutex = mutex - 1;
    full  = full + 1;
    empty = empty - 1;
    // producer produced the item
    x = x + 1;
    printf("\n Producer produces item %d",x);
    // Now the critical section is free by incrementing mutex to one
    mutex = mutex + 1;
}
void consumer()
{
    // mutex decrease to zero now the critical section is not free because already the consumer acquired the lock.
    mutex = mutex - 1;
    // consumer consumes the item in the slot
    full  = full - 1;
    // empty slot increment because the consumer consumed the item.
    empty = empty + 1;
    printf("\n Consumer consumes item %d",x);
    x = x - 1;
    mutex = mutex + 1;
}
int main()
{
    int i;
    char option;
    printf("\n1.Enter P for Producer""\n2.Enter C for Consumer""\n3.Enter E for Exit\n");
    for(i=1;i>0;i++)
    {
        printf("\n Enter your choice");
        scanf("%s",&option);
        switch(option)
        {
            case 'P':if((mutex==1)&&(empty!=0))
            {
                producer();
            }
            else
            {
                printf("Buffer is full!");
            }
            break;
            case 'C':if((mutex==1)&&(full!=0))
            {
                consumer();
            }
            else
            {
                printf("Buffer is empty!");
            }
            break;
            case 'E':exit(0);
            break;
        }
    }
}