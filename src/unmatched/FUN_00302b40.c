int igObject_ResetFields();

void FUN_00302b40(void *arg0, int arg1) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        temp_a0 = *(int *)(arg1 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_ResetFields(temp_a0);
        }
    }
}
