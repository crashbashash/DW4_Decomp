typedef struct { int *vt; int pad[71]; } Obj;
extern "C" {
int FUN_003bfde0(Obj *, int);
int beNDMWMdlPEBaseInfoWork_Construct(Obj *);
extern int DAT_0053d3e0[4];
extern void * DAT_00586dc8[4];
int beNDMWMdlEnemyInfoWork_GetVTable(void);
}
int beNDMWMdlEnemyInfoWork_GetVTable(void) {
    Obj o;
    int r;

    beNDMWMdlPEBaseInfoWork_Construct(&o);
    o.vt = &DAT_0053d3e0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053d3e0[0];
    FUN_003bfde0(&o, 0);
    return r;
}
