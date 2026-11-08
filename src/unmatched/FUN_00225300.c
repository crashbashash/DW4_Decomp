typedef struct {
    int f0[9];
    int server;
} Client;
extern Client DAT_0056d6c0;
extern Client DAT_0056d6e8;
extern Client DAT_0056d710;
extern Client DAT_0056d738;
extern Client DAT_0056d760;
extern char DAT_004e7858[];
extern char DAT_004e7870[];
extern char DAT_004e7898[];
void sceSifInitRpc(int mode);
int FUN_0010e0d8(void *cd, unsigned int id, int mode);
int FUN_0010d108(const char *fmt, ...);
void FUN_002252d8(const char *format, ...);
int sceMtapGetModVersion(void);
int FUN_00225300(void) {
    int i;
    int v;
    sceSifInitRpc(0);
    while (1) {
        if (FUN_0010e0d8(&DAT_0056d6c0, 0x80000901, 0) < 0) goto err;
        if (DAT_0056d6c0.server != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (FUN_0010e0d8(&DAT_0056d6e8, 0x80000902, 0) < 0) goto err;
        if (DAT_0056d6e8.server != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (FUN_0010e0d8(&DAT_0056d710, 0x80000903, 0) < 0) goto err;
        if (DAT_0056d710.server != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (FUN_0010e0d8(&DAT_0056d738, 0x80000904, 0) < 0) goto err;
        if (DAT_0056d738.server != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (FUN_0010e0d8(&DAT_0056d760, 0x80000905, 0) < 0) goto err;
        if (DAT_0056d760.server != 0) break;
        i = 0x10000;
        while (i--);
    }
    v = sceMtapGetModVersion();
    if (v >> 8 == 3) goto ok;
    FUN_0010d108(DAT_004e7870);
    FUN_0010d108(DAT_004e7898, 3, 0, v >> 8, v & 0xff);
    return 0;
err:
    FUN_002252d8(DAT_004e7858);
    return 0;
ok:
    return 1;
}
