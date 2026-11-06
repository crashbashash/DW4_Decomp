typedef struct { int *vt; int p4; int f8; int p12[2]; int f20; int f24; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int FUN_0033ec80(void *, int);
extern int DAT_0053d760[4];
extern void * DAT_00586dc8[4];
int beNDMWSaveCtrlInfo_GetVTable(void);
}
int beNDMWSaveCtrlInfo_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_0053d760[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053d760[0];
    FUN_0033ec80(&o, 0);
    return r;
}
