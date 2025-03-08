#define QueueDefaultSize 50
typedef struct CircularQueue{
    unsigned char Nextpointer;
    unsigned char Frontpointer;
    volatile unsigned char data[QueueDefaultSize];
    unsigned char size;
    unsigned char totalqueued;
}Queue;
//share this queue among SERCOM0 and SERCOM1

unsigned char Dequeue(Queue* queue);
void Enqueue(unsigned char data,Queue* queue);
unsigned char Peak(Queue* queue);