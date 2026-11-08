typedef struct {
    int value;
    char name[252];
} NameSend;

int FUN_0010e2a8(void *client, int rpc_number, int mode, void *send, int ssize, void *receive, int rsize, void *end_func, void *end_param);
extern int D_00481f18;
extern char D_00559280[];
extern int D_005592c0[];
extern NameSend D_00559340;

int sceSifLoadIopHeap(const char *name, int value)
{
    int i;
    if (D_00481f18 < 0) {
        return 0;
    }
    for (i = 0; i < 252; i++) {
        if ((D_00559340.name[i] = name[i]) == 0) {
            break;
        }
    }
    if (i == 252) {
        i = 251;
        D_00559340.name[251] = 0;
    }
    D_00559340.value = value;
    D_00559340.name[251] = 0;
    if (FUN_0010e2a8(D_00559280, 3, 0, &D_00559340, i + 5, D_005592c0, 4, 0, 0) < 0) {
        return -1;
    }
    return D_005592c0[0];
}
