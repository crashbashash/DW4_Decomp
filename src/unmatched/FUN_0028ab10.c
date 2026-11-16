unsigned char *MPV_SearchDelim();
int MPV_CheckDelim();
int FUN_0028ab10(unsigned char *p, int len) {
    unsigned char *q;

    q = MPV_SearchDelim(p, len, 64);
    if (q == 0) return 0;
    q += 4;
    len -= q - p;
    if (len <= 0) return 0;
    p = q;
    q = MPV_SearchDelim(p, len, -1);
    if (q == 0) return 0;
    if (!(MPV_CheckDelim(q) & 0x10)) return 0;
    q += 4;
    len -= q - p;
    if (len <= 0) return 0;
    return (*q >> 4) == 1;
}
