int Gap__Core__igMediaFile__vfunc_34(char *a, int c) {
    int n;
    if (*(unsigned char *)(a + 44) != 0) return -1;
    n = *(int *)(a + 56);
    if (n == 0) return -1;
    *(int *)(a + 56) = n - 1;
    if ((c & 0xff) != *(unsigned char *)(*(int *)(a + 60) + *(int *)(a + 56))) c = -1;
    return c;
}
