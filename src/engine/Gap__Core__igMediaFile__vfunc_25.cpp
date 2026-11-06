/* The result is a ternary; a conditional store lets the scheduler fill the delay slot. */
extern "C" {
extern char DAT_004f92f0[];
extern char DAT_004f9c48[];
extern char DAT_004f9c50[];
extern char DAT_004f9c58[];
extern char DAT_004f9c68[];
extern char DAT_004f9c78[];
extern char DAT_004f9c88[];
int FUN_002e30b0(...);
int igStrCmp(...);
extern int DAT_004f96a8[4];
extern int DAT_004f9c60[4];
extern int DAT_004f9c70[4];
extern int DAT_004f9c80[4];
extern int DAT_004f9c90[4];
extern int DAT_004fb418[4];
void **Gap__Core__igMediaFile__vfunc_25(void **arg0, int arg1, int arg2);
}
struct DW4SR4 { int w0; };
class DW4VCSR_92_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual DW4SR4 vX(int); };
void **Gap__Core__igMediaFile__vfunc_25(void **arg0, int arg1, int arg2) {
    DW4SR4 sp4C;
    DW4SR4 sp48;
    DW4SR4 sp44;
    DW4SR4 sp40;
    DW4SR4 sp3C;
    DW4SR4 sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;
    int var_v1;

    FUN_002e30b0();
    if (igStrCmp(arg2, &DAT_004f96a8[0]) == 0) {
        sp4C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(0));
        var_v1 = sp4C.w0;
        goto block_21;
    }
    if (igStrCmp(arg2, (int *)DAT_004f9c48) == 0) {
        sp48 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(4));
        var_v1 = sp48.w0;
        goto block_21;
    }
    if (igStrCmp(arg2, (int *)DAT_004f92f0) == 0) {
        sp44 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(1));
        var_v1 = sp44.w0;
        goto block_21;
    }
    if (igStrCmp(arg2, (int *)DAT_004f9c50) == 0) {
        sp40 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(5));
        var_v1 = sp40.w0;
        goto block_21;
    }
    if ((igStrCmp(arg2, (int *)DAT_004f9c58) == 0) || (igStrCmp(arg2, &DAT_004f9c60[0]) == 0)) {
        sp3C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(3));
        var_v1 = sp3C.w0;
        goto block_21;
    }
    if ((igStrCmp(arg2, (int *)DAT_004f9c68) == 0) || (igStrCmp(arg2, &DAT_004f9c70[0]) == 0)) {
        sp38 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(7));
        var_v1 = sp38.w0;
        goto block_21;
    }
    if ((igStrCmp(arg2, (int *)DAT_004f9c78) == 0) || (igStrCmp(arg2, &DAT_004f9c80[0]) == 0)) {
        sp34 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(2));
        var_v1 = sp34.w0;
        goto block_21;
    }
    if ((igStrCmp(arg2, (int *)DAT_004f9c88) == 0) || (igStrCmp(arg2, &DAT_004f9c90[0]) == 0)) {
        sp30 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(6));
        var_v1 = sp30.w0;
        goto block_21;
    }
    return 0;
block_21:
    return var_v1 == DAT_004fb418[0] ? 0 : arg0;
}
