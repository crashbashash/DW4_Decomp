extern "C" {
struct Ref { char pad0[4]; int f4; };
struct L { char pad0[8]; unsigned cnt; char pad12[4]; int *data; };
struct S { char pad0[28]; L * f28; L *getF28() const { return f28; } };
int FUN_001c5eb0(Ref **, S *, unsigned, unsigned);
int igObject_Destroy(Ref *);
unsigned FUN_001c6050(S *arg0, int arg1);
unsigned FUN_001c6050(S *arg0, int arg1) {
    Ref * sp2C;
    L *l;
    unsigned n;
    unsigned i;
    bool found;
    Ref *t;
    Ref *u;
    l = arg0->getF28();
    n = 0;
    if (l != 0) {
        n = l->cnt;
    }
    found = false;
    for (i = 0; i < n; i++) {
        int d = arg0->f28->data[i];
        if (d == arg1) {
            found = true;
            break;
        }
    }
    if (found) {
        FUN_001c5eb0(&sp2C, arg0, i, n);
        t = sp2C;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            u = sp2C;
            if (((unsigned long long) ((long long) u->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(u);
            }
        }
        return i;
    }
    return -1U;
}
}
