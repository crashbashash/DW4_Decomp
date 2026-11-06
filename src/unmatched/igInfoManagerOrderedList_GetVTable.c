/* stack-object GetVTable accessor with zeroed members and a trailing destructor call.py. */
typedef struct { int *vt; int w[5]; } Obj;
int igObject_InitHeader(void *);
int FUN_00233610(void *, int);
extern int DAT_0052cb60[4];
extern void * DAT_00586dc8[4];
int igInfoManagerOrderedList_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[4] = 0;
    o.vt = &DAT_0052cb60[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052cb60[0];
    FUN_00233610(&o, 0);
    return r;
}
