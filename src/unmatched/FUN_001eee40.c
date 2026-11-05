struct N { char pad[12]; int f12; int f16; struct N *f20; };
int memcpy();
int FUN_001eee40(struct N *arg0, int arg1) {
    int temp_s0;
    int var_s1;
    struct N *var_s2;

    var_s2 = arg0;
    var_s1 = var_s2->f16 - var_s2->f12;
    memcpy(arg1, var_s2->f12, var_s1);
    arg1 = arg1 + var_s1;
    while ((var_s2 = var_s2->f20) != 0) {
        arg1 = arg1 - 0x10;
        temp_s0 = var_s2->f16 - var_s2->f12;
        var_s1 = var_s1 - 0x10;
        memcpy(arg1, var_s2->f12, temp_s0);
        arg1 = arg1 + temp_s0;
        var_s1 = var_s1 + temp_s0;
    }
    return var_s1;
}