typedef struct {
    unsigned char command;
    unsigned char thread;
} ThreadRequest;
typedef struct {
    int pad;
    int next;
    ThreadRequest entries[512];
} ThreadRequestQueue;
extern int topThreadId;
extern int topThreadSema;
extern ThreadRequestQueue topThreadRequests;
int FUN_0010ae60(int thid);
int iSignalSema(int sema);
static inline int currentThreadId(void) {
    int thid;
    __asm__("li $3,-47\n\tsyscall\n\tmove %0,$2" : "=r"(thid) : : "$2", "$3", "memory");
    return thid;
}
int iSuspendThread(int thid) {
    int self = currentThreadId();
    int i;
    if (self != thid) return FUN_0010ae60(thid);
    if ((unsigned int)self >= 256 || topThreadId == 0) return -1;
    i = topThreadRequests.next & 0x1FF;
    topThreadRequests.next = i + 1;
    topThreadRequests.entries[i].command = 2;
    topThreadRequests.entries[i].thread = self;
    iSignalSema(topThreadSema);
    return self;
}
