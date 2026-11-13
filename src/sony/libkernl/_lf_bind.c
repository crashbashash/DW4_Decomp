typedef struct {
    int result;
    int extra;
    char name[252];
    char path[252];
} NameRequest;

typedef struct {
    char bytes[4];
} Version;

int sceSifBindRpc(void *client, unsigned int rpc_number, int mode);
int sceSifCallRpc(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481f20;
extern char D_00559640[];
extern char D_00559668[];
extern NameRequest D_00559440;

int _lf_bind(void)
{
    int i;
    if (D_00481f20 < 0) {
        while (1) {
            if (sceSifBindRpc(D_00559640, 0x80000006, 0) < 0) {
                return -1;
            }
            if (*(void **)(D_00559640 + 36) != 0) {
                D_00481f20 = 0;
                if (sceSifCallRpc(D_00559640, 255, 0, 0, 0, &D_00559440, 4, 0, 0) < 0) {
                    return 0xFFFEFFFF;
                }
                *(Version *)D_00559668 = *(Version *)&D_00559440;
                return 0;
            }
            i = 0x100000;
            while (i--);
        }
    }
    return 0;
}
