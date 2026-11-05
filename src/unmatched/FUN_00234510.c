/* 0x234510 — FUN_00234510. Verified byte-identical by tools/verify.py (wave3 sweep). */
int FUN_001236e8();
int FUN_002345b0();

int FUN_00234510(int a0, int a1, int a2, int *arg3) {
    int sp2C;

    if (FUN_002345b0(a0, a1, a2, &sp2C) != 0) {
        *arg3 = FUN_001236e8(sp2C);
        return 1;
    }
    return 0;
}
