/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; char pad[124]; };
extern "C" {
int beNDMWStatusCtrlBaseEquip_Construct(struct Obj *);
int FUN_003ba3d0(struct Obj *, int);
extern int DAT_0053eff0[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusMainSlot_GetVTable(void);
}
int beNDMWStatusMainSlot_GetVTable(void) {
    struct Obj obj;
    int t;

    beNDMWStatusCtrlBaseEquip_Construct(&obj);
    obj.vt = &DAT_0053eff0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053eff0[0];
    FUN_003ba3d0(&obj, 0);
    return t;
}
