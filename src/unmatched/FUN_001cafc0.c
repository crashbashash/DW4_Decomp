struct L { char p0[8]; int n; char pc[4]; int *items; };
int FUN_001cafc0(struct L *arg0, int *arg1, int arg2) {
    int n = arg0->n;
    int i = arg2;
    int r;
    while (i < n) {
        if (*arg1 == arg0->items[i]) { r = i; goto done; }
        i++;
    }
    r = -1;
done:
    return r;
}
