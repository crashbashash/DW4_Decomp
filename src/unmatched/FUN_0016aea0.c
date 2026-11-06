void FUN_0016aea0(int arg0, int arg1, int *arg2, int *arg3) {
    int *var_a2;
    int *var_a3;
    int temp_v1;
    int var_a1;
    int var_a1_2;

    var_a2 = arg2;
    var_a3 = arg3;
    switch (arg1) {
    case 0:
        var_a1 = 0;
        do {
            var_a1 += 1;
            *var_a2 = *var_a3;
            var_a3 += 1;
            var_a2 += 1;
        } while (var_a1 < 0x10);
        return;
    case 1:
        var_a1_2 = 0;
        do {
            temp_v1 = (var_a1_2 & 0xE7) | (((var_a1_2 >> 1) & 8) | ((var_a1_2 & 8) * 2));
            var_a1_2 += 1;
            *var_a2 = *(var_a3 + temp_v1);
            var_a2 += 1;
        } while (var_a1_2 < 0x100);
        return;
    }
}
