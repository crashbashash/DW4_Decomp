extern char DAT_004d2060[];
void FUN_00109b10(char *d, const char *msg, ...);
int FUN_00105be8(char *d, int *a, int *b, int *c, int *flags) {
    int ok = 1;

    *(int *)(d + *(int *)(d + 2088) * 320 + 1764) = 1;
    *(int *)(d + 456) = 1;
    if (*(int *)(d + 360) == 2) {
        a[5] = 0;
        a[4] = 0;
        a[1] = 0;
        a[0] = 0;
    }
    if (*(int *)(d + 396) == 3) {
        *b = 2;
    } else {
        *b = 1;
        c[0] = c[1] = *(int *)(d + 396) == 2;
    }
    if (*(int *)(d + 360) == 1) {
        FUN_00109b10(d, DAT_004d2060);
        ok = 0;
    }
    *flags &= ~1;
    return ok;
}
