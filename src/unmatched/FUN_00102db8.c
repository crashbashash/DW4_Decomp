void FUN_00102db8(char *arg0, int arg1) {
    int var_v0;
    char *var_a0;

    var_a0 = (char *)(arg0);
    var_v0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_a0 = 0;
            var_v0 -= 1;
            var_a0 += 1;
        } while (var_v0 != -1);
    }
}
