/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[27]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_003b6090(int *, int);
int FUN_003b9ba0(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int beNDMWWindowCtrl_Destroy(int *, int);
extern int DAT_0053edb0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusCtrlDisk_GetVTable(void);
}
int beNDMWStatusCtrlDisk_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &DAT_0053edb0[0];
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053edb0[0];
    FUN_003b9ba0(&obj.w[24], -1);
    FUN_003b6090(&obj.w[23], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[21], -1);
    beNDMWWindowCtrl_Destroy((int *)&obj, 0);
    return t;
}
