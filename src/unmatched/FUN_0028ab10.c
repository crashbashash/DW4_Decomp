unsigned char *FUN_0028de10();
int FUN_0028dc78();
int FUN_0028ab10(unsigned char *p, int len) {
    unsigned char *q;

    q = FUN_0028de10(p, len, 64);
    if (q == 0) return 0;
    q += 4;
    len -= q - p;
    if (len <= 0) return 0;
    p = q;
    q = FUN_0028de10(p, len, -1);
    if (q == 0) return 0;
    if (!(FUN_0028dc78(q) & 0x10)) return 0;
    q += 4;
    len -= q - p;
    if (len <= 0) return 0;
    return (*q >> 4) == 1;
}
