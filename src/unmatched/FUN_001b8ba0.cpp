extern "C" {
int igMatrix44f_SetIdentity(...);
int FUN_001d0130(...);
extern void * DAT_0055efe8[4];
int FUN_001b8ba0(void *arg0, int arg1);
}
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class DW4VC_104_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
int FUN_001b8ba0(void *arg0, int arg1) {
    int sp40[16];
    int *temp_s2;
    int temp_v0;
    void *temp_a1;
    void *temp_a2;

    temp_a2 = (void *)(*(int *)((char *)(arg0) + 52));
    temp_a1 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(temp_a2) + 16)) + 16) + (*(int *)(*(int *)((char *)(temp_a2) + 68) + (*(int *)((char *)(DAT_0055efe8[0]) + 8) * 4)) * 4)));
    temp_v0 = *(int *)((char *)(temp_a1) + 8);
    if (temp_v0 != 0) {
        temp_s2 = (int *)(*(int *)(*(int *)((char *)(temp_a1) + 16) + ((temp_v0 - 1) * 4)) + 0xC);
        FUN_001d0130(arg1, arg0, temp_s2, ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2)));
    } else {
        igMatrix44f_SetIdentity(sp40, temp_a1, temp_a2);
        FUN_001d0130(arg1, arg0, sp40, ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX());
    }
    return 0;
}
