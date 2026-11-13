int sceSifCallRpc(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
int _lf_bind(void);
int FUN_00112738(void);
extern char D_00559640[];
extern int D_00559440[];

int sceSifSearchModuleByAddress(int value)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (FUN_00112738() != 0) {
        return 0xFFFEFFFC;
    }
    D_00559440[0] = value;
    if (sceSifCallRpc(D_00559640, 10, 0, D_00559440, 4, D_00559440, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return D_00559440[0];
}
