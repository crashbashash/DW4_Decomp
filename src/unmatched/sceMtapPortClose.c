extern int DAT_0056d7c0[32];
int FUN_0010e2a8(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *arg);
void FUN_002252d8(const char *format, ...);
extern int DAT_0056d6e8;
extern char DAT_004e78e8[];
int sceMtapPortClose(int port) {
    DAT_0056d7c0[0] = port;
    if (FUN_0010e2a8(&DAT_0056d6e8, 1, 0, DAT_0056d7c0, 128, DAT_0056d7c0, 128, 0, 0) < 0) {
        FUN_002252d8(DAT_004e78e8);
        return 0;
    }
    return DAT_0056d7c0[1];
}
