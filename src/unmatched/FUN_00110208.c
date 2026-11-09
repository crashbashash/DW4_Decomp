typedef struct {
    int fd;
    int flags;
} FileIob;
typedef struct {
    int sema;
    int *result;
    int resultSize;
    int fd;
    int request;
    char arg[1024];
    void *buffer;
    unsigned int bufferSize;
    unsigned int argSize;
} Ioctl2Request;
typedef struct {
    int currentCount;
    int maxCount;
    int initCount;
    int waitThreads;
    unsigned int attribute;
    unsigned int option;
} SemaParam;
extern Ioctl2Request DAT_00557a80;
extern int DAT_00481efc;
extern char DAT_00559180[];
extern char DAT_005586c0[];
FileIob *get_iob(int fd);
void FUN_0010ef30(int command);
void FUN_0010ef60(void);
int FUN_0010f060(void);
void *memcpy(void *dst, const void *src, unsigned int n);
int CreateSema(SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
void sceSifWriteBackDCache(void *p, int size);
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
int FUN_00110208(int fd, int request, void *arg, unsigned int argSize, void *buffer, unsigned int bufferSize) {
    FileIob *iob = get_iob(fd);
    Ioctl2Request *packet = &DAT_00557a80;
    SemaParam param;
    int result;
    int sema;
    int status;
    FUN_0010ef30(26);
    if (DAT_00481efc == 0) FUN_0010f060();
    if (iob == 0 || iob->flags == 0) {
        FUN_0010ef60();
        return -9;
    }
    if (argSize > 1024 || bufferSize > 1024) {
        FUN_0010ef60();
        return -22;
    }
    if (arg == 0) {
        packet->argSize = 0;
    } else {
        memcpy(packet->arg, arg, argSize);
    }
    packet->fd = iob->fd;
    packet->request = request;
    packet->argSize = argSize;
    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = CreateSema(&param);
    packet->bufferSize = bufferSize;
    packet->result = &result;
    packet->resultSize = 4;
    packet->buffer = buffer;
    packet->sema = sema;
    sceSifWriteBackDCache(&DAT_00557a80, 1056);
    if (FUN_0010e2a8(DAT_00559180, 26, 0, &DAT_00557a80, 1056, DAT_005586c0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        FUN_0010ef60();
        return -11;
    }
    status = *(int *)((unsigned int)DAT_005586c0 | 0x20000000);
    FUN_0010ef60();
    if (status == 0) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}
