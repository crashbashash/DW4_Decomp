extern "C" {
int igObject_Destroy(...);
extern void * DAT_00586f68[4];
void FUN_002f00f0(void *arg0);
}
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
void FUN_002f00f0(void *arg0) {
    void *temp_s0;

    temp_s0 = (void *)(DAT_00586f68[0]);
    if (temp_s0 != arg0) {
        if (temp_s0 != 0) {
            DAT_00586f68[0] = (void *)(0);
            ((DW4VC_104_0 *)(((char *)(temp_s0) + 0)))->vX();
            *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_s0);
            }
        }
        DAT_00586f68[0] = (void *)(arg0);
    }
}
