typedef struct S0 { char pad4[4]; int f4; int f8; char pad20[8]; int f14; } S0;
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
int igObject_Destroy();

void FUN_0016a800(S0 *arg0) {
    S_temp_a0 *temp_a0;
    temp_a0 = (void *)(arg0->f4);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f4 = 0;
    arg0->f8 = 0;
    arg0->f14 = 0;
}
