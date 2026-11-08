extern "C" char DAT_004d3d10[16];
extern "C" char DAT_004d3d11[16];
extern "C" char DAT_004f95c0[16];
extern "C" char DAT_004fb198[16];
extern "C" char DAT_004fb1a0[16];
struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" igResult DAT_004fb410;
extern "C" int FUN_00129ef8(char *, char *, int *);
extern "C" int strlen(void);
extern "C" int strncmp(char *, char *, int);
extern "C" void strncpy(char *, char *, int);
extern "C" unsigned FUN_0012aff0(char *, char *);
extern "C" igResult igMetaEnum_GetValueByName(int, char *, int *);

extern "C" bool FUN_00306f10(char *arg0, int *arg1, int arg2, char *arg3) {
    char *s2;
    unsigned s1;
    bool s0;
    unsigned r;
    char *tok;
    int len;
    char buf[256];
    int sp18C;
    s2 = arg0;
    s1 = (unsigned)(arg0 + strlen());
    *arg1 = 0;
    s0 = true;
    while (*s2 && (DAT_004d3d10[*s2 + 1] & 8)) s2++;
    while (*s2 && *arg3 && *s2 == *arg3) { s2++; arg3++; }
    if (*arg3 == 0x25) {
        arg3++;
        if (*arg3 == 0x73) arg3++;
    }
    if (*arg3 != 0) {
        r = FUN_0012aff0(s2, arg3);
        if (r != 0) s1 = r; else s0 = false;
    }
    if (DAT_004d3d11[*s2] & 4) {
        if (strncmp(arg0, DAT_004fb198, 2) == 0) {
            if (FUN_00129ef8(arg0, DAT_004fb1a0, arg1) == 1) return 1;
        } else {
            if (FUN_00129ef8(arg0, DAT_004f95c0, arg1) == 1) return 1;
        }
    } else {
    while (*s2 && (unsigned)s2 < s1) {
        while (*s2 && (DAT_004d3d10[*s2 + 1] & 8)) s2++;
        tok = s2;
        while (*s2 && !(DAT_004d3d10[*s2 + 1] & 8) && (unsigned)s2 < s1) s2++;
        len = s2 - tok;
        if (*tok != 0) {
            if (len > 255) len = 255;
            strncpy(buf, tok, len);
            buf[len] = 0;
            sp18C = 0;
            if (igMetaEnum_GetValueByName(arg2, buf, &sp18C) == DAT_004fb410) { *arg1 |= (unsigned)sp18C; } else s0 = false;
        }
    }
    }
    return s0;
}
