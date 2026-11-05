void FUN_002d3150(int *arg0, int arg1) {
    int n = *(int *)(arg0[11] + 4);
    int i = 0;
    while (i < n) {
        ((void (*)(int))(*(int **)arg0[11])[i])(arg1);
        i++;
    }
}
