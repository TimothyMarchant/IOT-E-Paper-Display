#include "CircularQueue.h"
void Enqueue(unsigned char data,Queue* volatile queue){
    if (queue->totalqueued==queue->size){
        return;
    }
    queue->data[queue->Nextpointer]=data;
    queue->Nextpointer++;
    queue->Nextpointer=(queue->Nextpointer+1)%queue->size;
    queue->totalqueued++;
}
unsigned char Dequeue(Queue* volatile queue){
    //return 0 if nothing is in queue
    if (queue->totalqueued==0){
        return 0;
    }
    unsigned char newdata=queue->data[queue->Frontpointer];
    queue->Frontpointer=(queue->Frontpointer+1)%queue->size;
    queue->totalqueued--;
    return newdata;
}