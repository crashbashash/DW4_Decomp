int FUN_00241750(int *arg0, int *arg1) {
    int i = 0;
    while (arg1 != 0) {
        if (arg1 == arg0) {
            return i;
        }
        arg1 = (int *)arg1[5];
        i++;
    }
    return -1;
}
