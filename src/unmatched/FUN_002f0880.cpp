extern "C" {
extern int DAT_004fb410[4];
void FUN_002f0880(int *arg0, void **arg1, void *arg2);
}
struct DW4SR4 { int w0; };
class DW4VCSR_164_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual DW4SR4 vX(long long); };
void FUN_002f0880(int *arg0, void **arg1, void *arg2) {
    DW4SR4 sp2C;
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg2) + 32);
    if (temp_v1 != 0) {
        sp2C = ((DW4VCSR_164_1 *)(arg1))->vX((long long)temp_v1);
    }
    *arg0 = DAT_004fb410[0];
}
