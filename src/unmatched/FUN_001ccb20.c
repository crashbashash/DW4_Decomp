void FUN_001ccb20(int **arg0, int *arg1) {
    int *a;
    *arg0 = *(int **)arg1[4];
    a = *arg0;
    if (a != 0) {
        a[-1] = a[-1] + 1;
    }
}
