extern long long DAT_0056ae38[4];
void FUN_001f7500(void *arg0) {
    long long temp_a0;

    temp_a0 = *(long long *)((char *)(arg0) + 8);
    if (DAT_0056ae38[0] < temp_a0) {
        DAT_0056ae38[0] = temp_a0;
    }
}
