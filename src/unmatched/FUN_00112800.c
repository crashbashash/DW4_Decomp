typedef struct {
    int result;
    int extra;
    char name[252];
    char path[252];
} NameRequest;

typedef struct {
    char bytes[252];
} PathBlock;

int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int FUN_00112638(void);
int FUN_00112738(void);
void *memcpy(void *dst, const void *src, unsigned int size);
extern char D_00559640[];
extern NameRequest D_00559440;

int FUN_00112800(int id, int size, const void *data, int *out)
{
    int result;
    if (FUN_00112638() < 0) {
        return 0xFFFF0000;
    }
    if (FUN_00112738() != 0) {
        return 0xFFFEFFFC;
    }
    D_00559440.result = id;
    if (data != 0) {
        if (size > 252) {
            *(PathBlock *)D_00559440.path = *(const PathBlock *)data;
            D_00559440.extra = 252;
        } else {
            memcpy(D_00559440.path, data, size);
            D_00559440.extra = size;
        }
    } else {
        D_00559440.extra = 0;
    }
    if (FUN_0010e2a8(D_00559640, 6, 0, &D_00559440, 512, &D_00559440, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    result = D_00559440.result;
    *out = D_00559440.extra;
    return result;
}
