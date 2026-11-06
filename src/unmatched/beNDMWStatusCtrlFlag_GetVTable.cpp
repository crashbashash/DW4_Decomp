union U { int vt; char b[96]; };
extern "C" {
int igObject_InitHeader(char *);
int ObjectRef_Destruct_00150eb0(char *, int);
int beNDMWWindowCtrl_Destroy(char *, int);
extern int DAT_0053ee10[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusCtrlFlag_GetVTable(void);
}
int beNDMWStatusCtrlFlag_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&DAT_0053ee10[0];
    ps = &u.b[84];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053ee10[0];
    ObjectRef_Destruct_00150eb0(ps, -1);
    beNDMWWindowCtrl_Destroy(u.b, 0);
    return temp_s0;
}
