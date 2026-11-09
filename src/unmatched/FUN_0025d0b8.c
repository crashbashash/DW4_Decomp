extern int DAT_00498c5c;
extern short DAT_004ecff8[1024];
void FUN_0025d078(void);

int FUN_0025d0b8(const signed char *str, int len, short *k0, short *k1, short *k2)
{
    int i;
    short a;
    short b;
    short c;

    if (DAT_00498c5c == 0) {
        FUN_0025d078();
    }
    *k0 = 0;
    *k1 = 0;
    *k2 = 0;
    if (str == 0 && len <= 0) {
        return 0;
    }
    a = DAT_004ecff8[256];
    for (i = 0; i < len; i++) {
        a = DAT_004ecff8[a * DAT_004ecff8[128 + str[i]] % 1024];
    }
    b = DAT_004ecff8[512];
    for (i = 0; i < len; i++) {
        b = DAT_004ecff8[b * DAT_004ecff8[128 + str[i]] % 1024];
    }
    c = DAT_004ecff8[768];
    for (i = 0; i < len; i++) {
        c = DAT_004ecff8[c * DAT_004ecff8[128 + str[i]] % 1024];
    }
    *k0 = a;
    *k1 = b;
    *k2 = c;
    return 0;
}
