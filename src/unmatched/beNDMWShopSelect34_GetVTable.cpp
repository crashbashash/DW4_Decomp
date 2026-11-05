/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w[27]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_003b4050(struct Obj *, int);
extern int DAT_00540060[4];
extern void * DAT_00586dc8[4];
int beNDMWShopSelect34_GetVTable(void);
}
int beNDMWShopSelect34_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[26] = 0;
    obj.vt = &DAT_00540060[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540060[0];
    FUN_003b4050(&obj, 0);
    return r;
}
