extern int FUN_002b2ea0(int k);
extern void *FUN_002b25a8(void *h, int k);
extern int FUN_002b2e20(int k, void *e);
extern int FUN_002b2e60(int k, void *e);
int FUN_002b1b50(char *h, unsigned char k, int *out) {
    void *e;
    if (*(int *)(h + 12) < 110) return 0;
    switch (FUN_002b2ea0(k)) {
    case 0xC0:
        e = FUN_002b25a8(h, k);
        if (e == 0) return 0;
        *out = FUN_002b2e20(k, e);
        return 1;
    case 0xE0:
        e = FUN_002b25a8(h, k);
        if (e == 0) return 0;
        *out = FUN_002b2e60(k, e);
        return 1;
    }
    return 0;
}
