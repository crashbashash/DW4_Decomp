typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
typedef struct S0 { char pad16[16]; S_temp_a0 *f10; char pad20[52]; unsigned char f48; } S0;
int igObject_Destroy();

void FUN_001ab990(S0 *arg0) {
    S_temp_a0 *temp_a0;

    arg0->f48 &= 0xF7;
    temp_a0 = arg0->f10;
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f10 = 0;
}
