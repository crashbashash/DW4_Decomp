typedef struct S { char pad[12]; unsigned f12; unsigned f16; unsigned f20; unsigned f24; } S;
void FUN_0030da20(S *arg0, unsigned arg1, unsigned arg2) {
    unsigned temp_a2;

    arg0->f16 = arg1;
    arg0->f20 = arg2;
    temp_a2 = arg0->f12;
    if (temp_a2 != 0) {
        arg0->f24 = (arg0->f20 - arg0->f16) / temp_a2;
        if (((arg0->f20 - arg0->f16) % arg0->f12) != 0) {
            arg0->f24 = arg0->f24 + 1;
        }
    } else {
        arg0->f24 = 1;
    }
}
