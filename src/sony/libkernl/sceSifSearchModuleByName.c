typedef struct {
    int result;
    int pad;
    char name[252];
    char path[252];
} NameRequest;

int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int _lf_bind(void);
int FUN_00112738(void);
char *strncpy(char *dst, const char *src, unsigned int size);
extern char D_00559640[];
extern NameRequest D_00559440;

int sceSifSearchModuleByName(const char *name)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (FUN_00112738() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_00559440.name, name, 252);
    D_00559440.name[251] = 0;
    if (FUN_0010e2a8(D_00559640, 9, 0, &D_00559440, 512, &D_00559440, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return D_00559440.result;
}
