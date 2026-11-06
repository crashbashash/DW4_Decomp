/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[128]; };
extern "C" {
int FUN_003ba3d0(char *, int);
int beNDMWStatusCtrlBaseEquip_Construct(char *);
extern int DAT_0053ef40[4];
extern void * DAT_00586dc8[4];
int beNDMWStatusSubSlot_GetVTable(void);
}
int beNDMWStatusSubSlot_GetVTable(void) {
    union U u;
    int t;

    beNDMWStatusCtrlBaseEquip_Construct(u.b);
    u.vt = (int)&DAT_0053ef40[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053ef40[0];
    FUN_003ba3d0(u.b, 0);
    return t;
}
