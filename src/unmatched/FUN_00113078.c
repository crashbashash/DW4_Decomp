typedef struct {
    int result;
    int extra;
    char name[252];
    char path[252];
} NameRequest;

int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int FUN_00112638(void);
int FUN_00112738(void);
char *strncpy(char *dst, const char *src, unsigned int size);
extern char D_00559640[];
extern NameRequest D_00559440;

int FUN_00113078(const char *name, const char *path, int *out, int rpc_number)
{
    if (FUN_00112638() < 0) {
        return 0xFFFF0000;
    }
    if (FUN_00112738() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_00559440.name, name, 252);
    D_00559440.name[251] = 0;
    strncpy(D_00559440.path, path, 252);
    D_00559440.path[251] = 0;
    if (FUN_0010e2a8(D_00559640, rpc_number, 0, &D_00559440, 512, &D_00559440, 16, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    if (D_00559440.result == 0) {
        return 0xFFFEFFFD;
    }
    out[0] = D_00559440.result;
    out[1] = D_00559440.extra;
    return 0;
}
