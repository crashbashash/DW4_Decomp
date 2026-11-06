union U { int vt; char b[112]; };
extern "C" {
int FUN_003b4050(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053f410[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusSelect01_GetVTable(void);
}
int beNDMWStatusSelect01_GetVTable(void) {
    union U u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    *(int *)&u.b[80] = 0;
    *(int *)&u.b[108] = 0;
    u.vt = (int)&DAT_0053f410[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053f410[0];
    FUN_003b4050(u.b, 0);
    return t;
}
