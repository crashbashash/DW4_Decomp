int FUN_0027b768(void *arg0, int arg1) {
    int (*temp_v0)(int, int);

    if (arg1 == 1) {
        return *(int *)((char *)(arg0) + 12);
    }
    if (arg1 != 0) {
        temp_v0 = (int (*)(int, int))(*(int *)((char *)(arg0) + 28));
        if (temp_v0 != 0) {
            temp_v0(*(int *)((char *)(arg0) + 32), -3);
        }
    }
    return 0;
}
