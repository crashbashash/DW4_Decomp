typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
} SemaParam;

typedef struct {
    int sema;
    int *result;
    int result_size;
    int fd;
    int mode;
    char name[1024];
} OpenRequest;

void FUN_0010d890(void *addr, int size);

typedef struct {
    int sema;
    int *result;
    int result_size;
    char device[1024];
    char path[1024];
    unsigned char arg[1024];
    int flag;
    int arglen;
} MountRequest;

int FUN_0010ef30(int op);
int FUN_0010f060(void);
void FUN_0010ef60(void);
int CreateSema(SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481efc;
extern char D_00559180[];
extern MountRequest D_00557a80;
extern int D_005586c0[];

int FUN_00111640(const char *device, const char *path, int flag, const unsigned char *arg, int arglen)
{
    MountRequest *req = &D_00557a80;
    SemaParam param;
    int result;
    int sema;
    int status;
    int i;
    FUN_0010ef30(20);
    if (D_00481efc == 0) {
        FUN_0010f060();
    }
    for (i = 0; i < 1024; i++) {
        if ((req->device[i] = device[i]) == 0) {
            break;
        }
    }
    if (i == 1024) {
        req->device[1023] = 0;
    }
    for (i = 0; i < 1024; i++) {
        if ((req->path[i] = path[i]) == 0) {
            break;
        }
    }
    if (i == 1024) {
        req->path[1023] = 0;
    }
    if (arglen > 1024) {
        FUN_0010ef60();
        return -7;
    }
    for (i = 0; i < arglen; i++) {
        req->arg[i] = arg[i];
    }
    req->arglen = arglen;
    req->flag = flag;
    param.max_count = 1;
    param.init_count = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->result_size = 4;
    FUN_0010d890(&D_00557a80, 3092);
    if (FUN_0010e2a8(D_00559180, 20, 0, &D_00557a80, 3092, D_005586c0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        FUN_0010ef60();
        return -11;
    }
    status = *(int *)((unsigned int)D_005586c0 | 0x20000000);
    FUN_0010ef60();
    if (status == 0) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return result;
}
