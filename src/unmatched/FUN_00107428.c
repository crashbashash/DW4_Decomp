typedef struct {
    char pad0[360]; int x168;
    char pad1[452-364]; int x1c4;
    char pad2[2148-456]; int x864; int x868; int x86c;
} Dec;
void FUN_00107428(Dec *d, int n) {
    int fresh = 0;
    int m = 0;
    if (d->x168 != 3 && n != 0) {
        if (n < 0) {
            fresh = d->x86c == 0;
        }
        d->x86c = 0;
        m = n;
    }
    d->x1c4 = d->x864 + n;
    if (fresh && m >= n) {
        d->x1c4 = d->x864 + n + 1024;
    }
    {
        int a = d->x868;
        if (a < d->x1c4) a = d->x1c4;
        d->x868 = a;
    }
}
