int FUN_003064b0(void *arg0, int arg1) {
    int *list;
    int *e;
    int cnt;
    int i;

    list = (int *)*(int *)((char *)(arg0) + 8);
    cnt = 0;
    for (i = 0; i < list[2]; i++) {
        e = *(int **)(list[4] + (i * 4));
        if (e != 0 && e[2] == arg1) {
            cnt++;
        }
    }
    return cnt;
}
