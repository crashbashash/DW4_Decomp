typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad12[12]; int fC; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
int igObject_Destroy();

void Gap__Attrs__igTextureAttr__vfunc_36(S0 *arg0, S1 *arg1) {
    S_temp_a0 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (void *)(arg0->fC);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->fC = (int)(arg1);
}
