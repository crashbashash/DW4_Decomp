typedef struct S0 { char pad20[20]; int f14; } S0;
int FUN_00300f50();

void Gap__Gfx__igClut__vfunc_12(S0 *arg0) {
    int temp_a1;

    temp_a1 = arg0->f14;
    if (temp_a1 != 0) {
        FUN_00300f50(arg0, temp_a1);
        arg0->f14 = 0;
    }
}
