/* A request topThread carries out for an interrupt handler. */
typedef struct {
    unsigned char command;
    unsigned char arg;
} ThreadRequest;
typedef struct {
    int readIndex;
    int writeIndex;
    ThreadRequest entries[512];
} ThreadRequestQueue;

#define THREAD_REQUEST_ROTATE_READY_QUEUE 1

extern int topThreadId;
extern int topThreadSema;
extern ThreadRequestQueue topThreadRequests;
int iSignalSema(int sema);

int iRotateThreadReadyQueue(int priority) {
    int i;
    if ((unsigned int)priority >= 128 || topThreadId == 0) return -1;
    i = topThreadRequests.writeIndex & 0x1FF;
    topThreadRequests.writeIndex = i + 1;
    topThreadRequests.entries[i].command = THREAD_REQUEST_ROTATE_READY_QUEUE;
    topThreadRequests.entries[i].arg = priority;
    iSignalSema(topThreadSema);
    return priority;
}
