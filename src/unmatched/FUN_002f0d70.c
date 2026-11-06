typedef struct S0 { char pad4[4]; int f4; } S0;
int igObject_Destroy();

void FUN_002f0d70(int dummy0, S0 *arg1) {
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 - 1));
        if (((unsigned long long) ((long long) arg1->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(arg1);
        }
    }
}
