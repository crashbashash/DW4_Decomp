extern "C" {
int memcpy(...);
int FUN_00329070(void **arg0, int arg1, unsigned int arg2, unsigned int arg3);
}
struct DW4SR4 { int w0; };
class DW4VC_68_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual int vX(int, int); };
class DW4VCSR_72_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual DW4SR4 vX(int, int); };
int FUN_00329070(void **arg0, int arg1, unsigned int arg2, unsigned int arg3) {
    DW4SR4 sp5C;
    DW4SR4 sp58;
    int temp_v0;

    if (arg2 < arg3) {
        sp5C = ((DW4VCSR_72_2 *)(arg0))->vX((int)(arg1 + arg2), (int)(arg3 - arg2));
        return arg1;
    }
    if (((DW4VC_68_2 *)(arg0))->vX((int)(arg1 + arg3), (int)(arg2 - arg3)) != -1) {
        return arg1;
    }
    temp_v0 = ((DW4VC_68_2 *)(arg0))->vX((int)(0), (int)(arg2));
    if (temp_v0 == -1) {
        return 0;
    }
    memcpy(temp_v0, arg1, arg3);
    sp58 = ((DW4VCSR_72_2 *)(arg0))->vX((int)(arg1), (int)(arg3));
    return temp_v0;
}
