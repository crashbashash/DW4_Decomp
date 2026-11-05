/* FUN_002e7030 - ring-buffer read: modulo, C++ virtual call (slot 108), result stored in both arms. Alternate compiler -O3. Verified byte-identical by tools/verify.py. */
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
struct Z { char pad0[80]; int f80; int f84; int f88; char pad1[12]; V *f104; char pad2[152]; int f260; int f264; };
extern "C" {
int memcpy(int, int, int);
void FUN_002e7030(int *arg0, Z *arg1);
}
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void FUN_002e7030(int *arg0, Z *arg1) {
    int hi;
    int a2;
    hi = (arg1->f260 - arg1->f80) % arg1->f260;
    if (hi > 0) {
        memcpy(arg1->f264, arg1->f264 + arg1->f80, hi);
    }
    a2 = arg1->f260 - hi;
    if (arg1->f88 < hi + (arg1->f84 + a2)) {
        a2 = (arg1->f88 - arg1->f84) - hi;
    }
    if (arg1->f104->vX(arg1->f264 + hi, a2, 1) != 1) {
        *arg0 = DAT_004fb418[0];
    } else {
        arg1->f80 = 0;
        *arg0 = DAT_004fb410[0];
    }
}
