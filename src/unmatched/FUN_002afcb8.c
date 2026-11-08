typedef int (*Fn)(int, int, int, int);
int FUN_002afcb8(Fn **tbl, int k) {
    int i;
    int r = 0;
    for (i = 0; i < 15; i++) {
        Fn *t = *tbl++;
        if (t == 0) break;
        r = t[k](0, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}
