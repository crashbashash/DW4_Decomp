typedef struct {
    unsigned char command;
    unsigned char thread;
} ThreadRequest;
typedef struct {
    int pad;
    int next;
    ThreadRequest entries[512];
} ThreadRequestQueue;
extern int DAT_00481e58;
extern int DAT_00555680;
extern ThreadRequestQueue DAT_00555688;
int FUN_0010ae20(int thid);
int iSignalSema(int sema);
static inline int currentThreadId(void) {
    int thid;
    __asm__("li $3,-47\n\tsyscall\n\tmove %0,$2" : "=r"(thid) : : "$2", "$3", "memory");
    return thid;
}
int iWakeupThread(int thid) {
    int self = currentThreadId();
    int i;
    if (self != thid) return FUN_0010ae20(thid);
    if ((unsigned int)self >= 256 || DAT_00481e58 == 0) return -1;
    i = DAT_00555688.next & 0x1FF;
    DAT_00555688.next = i + 1;
    DAT_00555688.entries[i].command = 0;
    DAT_00555688.entries[i].thread = self;
    iSignalSema(DAT_00555680);
    return self;
}
