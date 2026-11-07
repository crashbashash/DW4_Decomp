int FUN_003064b0(int arg0, int arg1) {
    int *e;
    int i;
    int *list;
    int cnt;

    list = *(int **)(arg0 + 8);
    cnt = 0;
    arg0 = list[2];
    for (i = 0; i < arg0; i++) {
        e = *(int **)(list[4] + (i * 4));
        if (e != 0 && e[2] == arg1) {
            cnt++;
        }
    }
    return cnt;
}
