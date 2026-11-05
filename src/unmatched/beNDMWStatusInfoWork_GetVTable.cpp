/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[11]; };
extern "C" {
int FUN_003b6090(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053db00[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusInfoWork_GetVTable(void);
}
int beNDMWStatusInfoWork_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053db00[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053db00[0];
    FUN_003b6090(&obj.w[6], -1);
    FUN_003b6090(&obj.w[5], -1);
    FUN_003b6090(&obj.w[4], -1);
    FUN_003b6090(&obj.w[3], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[2], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[1], -1);
    return r;
}
