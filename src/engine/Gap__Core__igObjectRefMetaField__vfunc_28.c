int igObject_ResetFields(int);

void Gap__Core__igObjectRefMetaField__vfunc_28(void *arg0, int arg1) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + *(int *)((char *)arg0 + 8));
    if (temp_a0 != 0) {
        igObject_ResetFields(temp_a0);
    }
}
