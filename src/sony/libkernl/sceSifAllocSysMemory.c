int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481f18;
extern char D_00559280[];
extern int D_005592c0[];
extern int D_00559300[];

int sceSifAllocSysMemory(int a, int b, int c)
{
    if (D_00481f18 < 0) {
        return 0;
    }
    D_00559300[0] = b;
    D_00559300[1] = a;
    D_00559300[2] = c;
    if (FUN_0010e2a8(D_00559280, 4, 0, D_00559300, 12, D_005592c0, 4, 0, 0) < 0) {
        return 0;
    }
    return D_005592c0[0];
}
