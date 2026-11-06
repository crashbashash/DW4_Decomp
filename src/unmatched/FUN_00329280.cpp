struct R { int w0; };
class O { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v17();
 virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual R v25(int, int, int);
 virtual int v26(...);
 virtual int v27(int);
 virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v40(int);
 virtual void d41(); virtual void d42(); virtual void d43(); virtual R v44(int, int, int);
};
extern "C" unsigned FUN_00329280(O *self, unsigned a, int n);
unsigned FUN_00329280(O *self, unsigned a, int n) {
    unsigned r = -1;
    if (a == 0) {
        unsigned t = self->v27(n);
        r = t;
        if (t == (unsigned)-1) r = self->v40(n);
    } else if (self->v26() != 0) {
        r = a;
    } else {
        unsigned c = self->v17();
        if (c == a) {
            r = self->v40(n);
            if (r != a) {
                if (r != (unsigned)-1) {
                    self->v40(-n);
                    r = -1;
                }
            }
        } else {
            unsigned e = a + n;
            if (a <= c && c < e && self->v26(a, c - a) != 0) {
                int m = e - c;
                r = self->v40(m);
                if (r != a && r != (unsigned)-1) {
                    self->v40(-m);
                    r = -1;
                }
            }
        }
    }
    if (r != (unsigned)-1) {
        R x = self->v44(r, n, 1);
        R y = self->v25(3, r, n);
    }
    return r;
}
