/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; char pad[252]; };
extern "C" {
int FUN_00350410(struct W *, int);
int beModelCtrlInfoWork_Construct(struct W *);
extern int DAT_0053d500[4];
extern char *DAT_00586dc8[4];
int beNDMWMdlPlayer2InfoWork_GetVTable(void);
}
int beNDMWMdlPlayer2InfoWork_GetVTable(void) {
    struct W o;
    int r;

    beModelCtrlInfoWork_Construct(&o);
    o.vt = DAT_0053d500;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053d500;
    FUN_00350410(&o, 0);
    return r;
}
