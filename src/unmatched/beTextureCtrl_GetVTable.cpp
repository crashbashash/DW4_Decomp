typedef struct { int *vt; int w[8]; int s; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int FUN_00342460(void *, int);
int FUN_0033f5e0(void *, int);
extern int DAT_0053c300[4];
extern void * DAT_00586dc8[4];
int beTextureCtrl_GetVTable(void);
}
int beTextureCtrl_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = &DAT_0053c300[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053c300[0];
    FUN_00342460(&o.s, -1);
    FUN_0033f5e0(&o, 0);
    return r;
}
