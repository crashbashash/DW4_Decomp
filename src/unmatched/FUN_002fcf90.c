struct S { char pad[8]; int base; char pad2[8]; unsigned short n; };
int FUN_002fcf90(struct S *arg0, unsigned char *arg1, unsigned char *arg2) {
    unsigned char *p1;
    unsigned char *p2;
    int n;
    int i;
    int b;
    b = arg0->base;
    n = arg0->n;
    p1 = arg1 + b;
    p2 = arg2 + b;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return 0;
        }
    }
    return 1;
}
