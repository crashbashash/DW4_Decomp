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

typedef struct {
    int fd;
    int mode;
    int pad[2];
} FileEntry;

int FUN_0010ef30(int op);
int FUN_0010f060(void);
void FUN_0010ef60(void);
FileEntry *get_iob(int fd);
int CreateSema(SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int sceSifCallRpc(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481efc;
extern char D_00559180[];
extern OpenRequest D_00557a80;
extern int D_005586c0[];
extern FileEntry D_00558f80[];

int FUN_0010f5b8(int fd)
{
    OpenRequest *req = &D_00557a80;
    FileEntry *entry;
    SemaParam param;
    int result;
    int sema;
    int status;
    entry = get_iob(fd);
    FUN_0010ef30(1);
    if (D_00481efc == 0) {
        FUN_0010ef60();
        return -1;
    }
    if (entry == 0 || entry->mode == 0) {
        FUN_0010ef60();
        return -9;
    }
    req->fd = entry->fd;
    req->mode = entry - D_00558f80;
    param.max_count = 1;
    param.init_count = 0;
    param.option = 0;
    sema = CreateSema(&param);
    req->sema = sema;
    req->result = &result;
    req->result_size = 4;
    if (sceSifCallRpc(D_00559180, 1, 0, req, 20, D_005586c0, 4, 0, 0) < 0) {
        DeleteSema(sema);
        FUN_0010ef60();
        return -11;
    }
    entry->mode = 0;
    status = *(int *)((unsigned int)D_005586c0 | 0x20000000);
    FUN_0010ef60();
    if (status == 0) {
        DeleteSema(sema);
        return -11;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (result < 0) {
        return result;
    }
    return 0;
}
