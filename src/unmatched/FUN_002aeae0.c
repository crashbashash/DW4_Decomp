extern int D_004bea90;
extern int FUN_002aec58(char *h, int *a, int *b);
int FUN_002aeae0(char *h, int *a, int *b) {
    int r = FUN_002aec58(h, a, b);
    h += 0xD28;
    if (r == 0) {
        return r;
    }
    *a = *(int *)(h + 680);
    *b = D_004bea90;
    return 0;
}
