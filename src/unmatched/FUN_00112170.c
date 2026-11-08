int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481f18;
extern char D_00559280[];
extern int D_005592c0[];
extern int D_00559300[];

int FUN_00112170(int value)
{
    if (D_00481f18 < 0) {
        return 0;
    }
    D_00559300[0] = value;
    if (FUN_0010e2a8(D_00559280, 1, 0, D_00559300, 4, D_005592c0, 4, 0, 0) < 0) {
        return 0;
    }
    return D_005592c0[0];
}
