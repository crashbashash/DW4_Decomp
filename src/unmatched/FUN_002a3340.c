int FUN_00291250();

void FUN_002a3340(void *arg0, int *arg1, int arg2) {
    int *var_s0;
    int temp_a1;
    int temp_a2;
    int temp_s2;
    int var_s1;

    temp_s2 = **(int **)((char *)(arg0) + 8120);
    if (temp_s2 != 0) {
        var_s1 = 0;
        if (arg2 > 0) {
            var_s0 = (int *)(arg1);
            do {
                temp_a2 = *var_s0;
                var_s0 += 1;
                temp_a1 = var_s1;
                var_s1 += 1;
                FUN_00291250(temp_s2, temp_a1, temp_a2);
            } while (var_s1 < arg2);
        }
    }
}
