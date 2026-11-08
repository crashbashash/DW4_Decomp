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

int FUN_0010ef30(int op);
int FUN_0010f060(void);
void FUN_0010ef60(void);
int CreateSema(SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481efc;
extern char D_00559180[];
extern OpenRequest D_00557a80;
extern int D_005586c0[];

int FUN_001114a8(const char *name, int mode)
{
    OpenRequest *req = &D_00557a80;
    SemaParam param;
    int result;
    int sema;
    int status;
    int i;
    FUN_0010ef30(19);
    if (D_00481efc == 0) {
        FUN_0010f060();
    }
    for (i = 0; i < 1024; i++) {
        if ((req->name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 1024) {
        req->name[1023] = 0;
    }
    req->mode = mode;
    param.max_count = 1;
    param.init_count = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->result = &result;
    req->sema = sema;
    req->result_size = 4;
    if (FUN_0010e2a8(D_00559180, 19, 0, &D_00557a80, 1044, D_005586c0, 4, 0, 0) < 0) {
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
