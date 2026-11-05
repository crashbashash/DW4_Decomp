struct N { char pad[24]; struct N *f24; char pad2[4]; struct N *f32; char pad3[4]; int f40; int f44; };
int FUN_00242430();
int FUN_00242430(struct N *arg0, int arg1, int *arg2) {
    struct N *var_s1;

    if ((arg1 == arg0->f40) || (arg1 == arg0->f44)) {
        return 1;
    }
    *arg2 += 1;
    for (var_s1 = arg0->f24; var_s1 != 0; var_s1 = var_s1->f32) {
        if (FUN_00242430(var_s1, arg1, arg2) != 0) {
            return 1;
        }
    }
    *arg2 -= 1;
    return 0;
}