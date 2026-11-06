void FUN_0020c7b0(char *arg0, char *arg1) {
    char *p = arg0;
    while (*(char **)(p + 32) != 0) p = *(char **)(p + 32);
    *(char **)(p + 32) = arg1;
    *(int *)(arg1 + 32) = 0;
    arg0[71] = arg0[71] + 1;
}
