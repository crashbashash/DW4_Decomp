int FUN_002adc40(int, int);
void FUN_002a27d8(int, int *, int *);

int FUN_002a1d28(int h, int dflt) {
    int v = FUN_002adc40(h, 59);
    int a;
    int b;

    if (v == 1) {
        return dflt;
    }
    if (v < 2) {
        return dflt;
    }
    if (v == 2) {
        FUN_002a27d8(h, &a, &b);
        return b >= 2 ? v : dflt;
    }
    return dflt;
}
