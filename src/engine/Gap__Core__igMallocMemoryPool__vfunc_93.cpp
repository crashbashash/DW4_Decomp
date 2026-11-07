extern "C" {
extern int DAT_004fb418[4];
extern int DAT_004fb410[4];
}
typedef struct H { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } H;
typedef struct T { unsigned char b : 7; unsigned char flag : 1; } T;
typedef struct S { char p[120]; int f120; inline int Chk(int y) { if (f120 < 64 && y >= 64) return 0; return 1; } } S;
static inline int Chk(int x, int y) { if (x < 64) { if (y >= 64) { return 0; } return 1; } return 1; }
static inline int Chk2(int x, int y) { int r = 1; if (x < 64) { r = 0; if (y >= 64) { } else { r = 1; } } return r; }

class DW4VC_364_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int vX(); };

extern "C" void Gap__Core__igMallocMemoryPool__vfunc_93(int *arg0, S *arg1, char *arg2, DW4VC_364_0 *arg3) {
    int v = arg3->vX();
    int ok;
    H *h;
    int a;
    ok = arg1->Chk(v);
    if (ok != 0) {
        h = (H *)(arg2 - 4);
        if (((T *)(arg2 - 1))->flag == 1) {
            h = (H *)(arg2 - 12);
        }
        a = arg3->vX() >> 1;
        h->lo = a;
        if (h->flag == 1) {
            h->ext = a >> 5;
        }
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
