struct S { char p[62]; unsigned short f62; char q[12]; int f76; int f80; };
int FUN_00320ea0(struct S *arg0, int arg1) {
    int base = arg0->f80;
    if (base != 0 && arg1 >= 0 && arg1 <= arg0->f76) {
        return base + arg1 * arg0->f62;
    }
    return 0;
}
