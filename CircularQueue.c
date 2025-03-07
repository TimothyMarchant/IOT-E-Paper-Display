#include "CircularQueue.h"
void Enqueue(unsigned char data){
    if (SER_queue.totalqueued==SER_queue.size){
        return;
    }
    SER_queue.data[SER_queue.Nextpointer]=data;
    SER_queue.Nextpointer++;
    SER_queue.Nextpointer=(SER_queue.Nextpointer+1)%SER_queue.size;
    SER_queue.totalqueued++;
}
unsigned char Dequeue(void){
    //return 0 if nothing is in queue
    if (SER_queue.totalqueued==0){
        return 0;
    }
    unsigned char newdata=SER_queue.data[SER_queue.Frontpointer];
    SER_queue.Frontpointer=(SER_queue.Frontpointer+1)%SER_queue.size;
    SER_queue.totalqueued--;
    return newdata;
}