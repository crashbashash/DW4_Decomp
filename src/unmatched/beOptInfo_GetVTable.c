/* stack-object GetVTable accessor with two released members; verified by tools/verify.py. */
typedef struct { int *vt; int p4; int f8; int pad[4]; int a; int b; int tail[3]; } Obj;
int igObject_InitHeader(void *);
int StringRef_Destruct_00130720(void *, int);
int FUN_00131b20(void *, int);
extern int DAT_00538590[4];
extern void * DAT_00586dc8[4];
int beOptInfo_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_00538590[0];
    o.a = 0;
    o.b = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00538590[0];
    StringRef_Destruct_00130720(&o.b, -1);
    StringRef_Destruct_00130720(&o.a, -1);
    FUN_00131b20(&o, 0);
    return r;
}
