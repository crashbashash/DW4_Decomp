/* Returning the value keeps the index web in v0; the base load reuses arg0. */
int FUN_00127488(int arg0, int arg1) {
    int v;
    if (arg1 != 0) {
        v = *(int *)(arg1 + 4);
        arg0 = *(int *)(arg0 + 76);
        v = v << 2;
        v = v + arg0;
        *(int *)(arg1 + 0) = *(int *)v;
        *(int *)v = arg1;
    }
    return v;
}
