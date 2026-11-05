typedef struct S1 { char pad4[4]; int f4; } S1;
extern "C" {
void *FUN_001a8c30(...);
int FUN_001ab6c0(...);
int FUN_001abb50(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int FUN_001ab770(void *arg0, void **arg1, void **arg2);
}
class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
int FUN_001ab770(void *arg0, void **arg1, void **arg2) {
    int temp_v0_2;
    int temp_a0;
    int var_s0;
    int temp_s1;
    int var_s2;
    void *temp_v0;
    temp_v0 = (void *)(FUN_001a8c30(igObject_GetAllocator()));
    FUN_001abb50(temp_v0, arg1);
    temp_s1 = ((DW4VC_96_0 *)(arg1))->vX();
    var_s0 = 0;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_v0_2 = FUN_001ab6c0(arg0, ((DW4VC_104_1 *)(arg1))->vX((int)(var_s2)));
        if (temp_v0_2 != -1) {
            var_s0 += 1;
        }
        *(int *)(*(int *)((char *)(temp_v0) + 12) + var_s2 * 4) = temp_v0_2;
    }
    if (var_s0 != 0) {
        *(int *)((char *)(temp_v0) + 16) = var_s0;
        ObjectList_AppendRetained(*(int *)((char *)(arg0) + 16), temp_v0);
        *arg2 = temp_v0;
    } else {
        *arg2 = 0;
    }
    ((S1 *)temp_v0)->f4 = (int)((int) (((S1 *)temp_v0)->f4 - 1));
    if (((unsigned long long) ((long long) ((S1 *)temp_v0)->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    return var_s0;
}
