extern int DAT_004C22F0[4];
int strcasecmp();
int strlen();

int FUN_0030ba90(void *arg0, char *arg1) {
    int temp_a0;
    int temp_v0;
    int var_a1;
    char *var_s0;
    unsigned int temp_s2;

    var_s0 = *(char **)((char *)(arg0) + 8);
    temp_s2 = *(int *)((char *)(arg0) + 12);
    if (var_s0 == 0) {
        var_s0 = (char *)DAT_004C22F0[0];
    }
    temp_v0 = strlen(arg1);
    var_a1 = 1;
    if (*arg1 == 0x2E) {
        var_a1 = 0;
    }
    if (temp_s2 < (unsigned int) (temp_v0 + var_a1)) {
        return 0;
    }
    temp_a0 = temp_s2 - temp_v0;
    if (*(var_s0 + (temp_a0 - var_a1)) != 0x2E) {
        return 0;
    }
    temp_v0 = strcasecmp(var_s0 + temp_a0, arg1);
    return temp_v0 == 0;
}
