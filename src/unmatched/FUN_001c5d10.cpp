extern "C" {

int FUN_001c5d10(void *arg0, int arg1);
}
class DW4VC_140_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int, int); };
int FUN_001c5d10(void *arg0, int arg1) {
    int var_s0;
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 28));
    if (temp_v0 != 0) {
        var_s0 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_s0 = 0;
    }
    if (((DW4VC_140_2 *)(((char *)(arg0) + 0)))->vX((int)(var_s0), (int)(arg1)) != 0) {
        return var_s0 + 1;
    }
    return -1;
}
