typedef struct S0 { char pad16[16]; unsigned char f10; char pad24[7]; int f18; char pad128[100]; int f80; int f84; int f88; } S0;
int FUN_001eedf0();
int FUN_001eee40();
int FUN_001eeed0();
int FUN_00300db0();

void FUN_0017f630(S0 *arg0) {
    int temp_a0;
    int temp_a1;

    if (arg0->f10 != 0) {
        temp_a0 = arg0->f80;
        if ((temp_a0 != 0) && ((temp_a1 = arg0->f18, (temp_a1 == 3)) || (temp_a1 == 2)) && (arg0->f84 == 0)) {
            arg0->f84 = FUN_00300db0(arg0, FUN_001eedf0(temp_a0, temp_a1), 0x10);
            FUN_001eee40(arg0->f80, arg0->f84);
            arg0->f88 = FUN_001eeed0(arg0->f80);
        }
    }
}
