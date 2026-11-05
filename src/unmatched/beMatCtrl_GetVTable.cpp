/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[19]; };
extern "C" {
int FUN_0033f5e0(struct Obj *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053aad0[4];
extern void * DAT_00586dc8[4];
int beMatCtrl_GetVTable(void);
}
int beMatCtrl_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053aad0[0];
    obj.w[13] = 0;
    obj.w[14] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053aad0[0];
    ObjectRef_Destruct_00150eb0(&obj.w[14], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[13], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}
