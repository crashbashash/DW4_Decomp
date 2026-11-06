typedef struct { int *vt; int w[6]; int s; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int FUN_00199450(void *, int);
int FUN_0033ec80(void *, int);
extern int DAT_00537040[4];
extern void * DAT_00586dc8[4];
int beMeterCtrlInfo_GetVTable(void);
}
int beMeterCtrlInfo_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = &DAT_00537040[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00537040[0];
    FUN_00199450(&o.s, -1);
    FUN_0033ec80(&o, 0);
    return r;
}
