typedef struct X { char pad[4]; int f4; } X;
int FUN_002295b0();
int FUN_0022a040();
int FUN_002fd610();
int StringChunk_ReleaseHeader();
int igObject_Destroy();
int FUN_0022a1e0(X **arg0, int arg1, char **arg2, int arg3) {
    X *volatile sp4C;
    char *volatile sp48;
    X *volatile sp44;
    char *s;
    X *t;
    int *hd;
    int temp_s2;
    int v;
    sp48 = *arg2;
    s = sp48;
    if (s != 0) {
        *(int *)(s - 4) = *(int *)(s - 4) + 1;
    }
    temp_s2 = FUN_0022a040(arg1, &sp48, arg3);
    s = sp48;
    if (s != 0) {
        hd = (int *)(s - 8);
        v = *(int *)(s - 4) - 1;
        *(int *)(s - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    if (temp_s2 == 0) {
        *arg0 = 0;
        t = *arg0;
        if (t != 0) {
            t->f4 = t->f4 + 1;
        }
        return;
    }
    FUN_002fd610(&sp44, temp_s2);
    sp4C = sp44;
    t = sp4C;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    t = sp44;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        t = sp44;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    t = sp4C;
    if (t != 0) {
        FUN_002295b0(arg1, t);
    }
    *arg0 = sp4C;
    t = *arg0;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    t = sp4C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
