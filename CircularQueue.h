#define QueueDefaultSize 50
typedef struct CircularQueue{
    unsigned char Nextpointer;
    unsigned char Frontpointer;
    volatile unsigned char data[QueueDefaultSize];
    unsigned char size;
    unsigned char totalqueued;
}Queue;
//share this queue among SERCOM0 and SERCOM1
Queue SER_queue={0,0,{},QueueDefaultSize,0};
unsigned char Dequeue(void);
void Enqueue(unsigned char data);
unsigned char Peak(void);