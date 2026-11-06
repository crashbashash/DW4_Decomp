/* stack-object GetVTable accessor with two released members.py. */
typedef struct { int *vt; int p4; int f8; int pad[4]; int a; int b; int tail[4]; } Obj;
int igObject_InitHeader(void *);
int StringRef_Destruct_00130720(void *, int);
int FUN_0019c840(void *, int);
int FUN_0014f4e0(void *, int);
extern int DAT_0052f040[4];
extern void * DAT_00586dc8[4];
int igObjectDirEntry_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.vt = &DAT_0052f040[0];
    o.a = 0;
    o.b = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0052f040[0];
    StringRef_Destruct_00130720(&o.b, -1);
    FUN_0019c840(&o.a, -1);
    FUN_0014f4e0(&o, 0);
    return r;
}
