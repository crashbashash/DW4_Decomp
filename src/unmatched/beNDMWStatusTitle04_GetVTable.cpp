typedef struct { int *vt; int w[19]; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int FUN_003b3030(void *, int);
extern int DAT_0053f560[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusTitle04_GetVTable(void);
}
int beNDMWStatusTitle04_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053f560[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053f560[0];
    FUN_003b3030(&o, 0);
    return r;
}
