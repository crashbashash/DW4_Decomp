typedef struct {
    int result;
    int extra;
    char name[252];
    char path[252];
} NameRequest;

typedef struct {
    char bytes[252];
} PathBlock;

int sceSifCallRpc(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int _lf_bind(void);
int FUN_00112738(void);
void *memcpy(void *dst, const void *src, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int size);
extern char D_00559640[];
extern NameRequest D_00559440;

int _sceSifLoadModule(const char *name, int size, const void *data, int *out, int rpc_number)
{
    int result;
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (FUN_00112738() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_00559440.name, name, 252);
    D_00559440.name[251] = 0;
    if (data != 0) {
        if (size > 252) {
            *(PathBlock *)D_00559440.path = *(const PathBlock *)data;
            D_00559440.result = 252;
        } else {
            memcpy(D_00559440.path, data, size);
            D_00559440.result = size;
        }
    } else {
        D_00559440.path[0] = 0;
        D_00559440.result = 0;
    }
    if (sceSifCallRpc(D_00559640, rpc_number, 0, &D_00559440, 512, &D_00559440, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    result = D_00559440.result;
    *out = D_00559440.extra;
    return result;
}
