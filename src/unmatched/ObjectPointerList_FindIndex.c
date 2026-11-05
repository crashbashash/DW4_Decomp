int ObjectPointerList_FindIndex(char *arg0, int arg1) {
    int *d = *(int **)(arg0 + 8);
    int n = *(int *)(arg0 + 12);
    int i;
    int v;
    for (i = 0; i < n; i++) {
        v = d[i];
        if (v == arg1) {
            return i;
        }
    }
    return -1;
}
