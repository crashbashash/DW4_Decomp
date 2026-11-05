/* 0x0013e230 - FUN_0013e230. Vertex stream flag update with per-element virtual setters and two counted array releases (released object read once into a local); default compiler. Verified byte-identical by tools/verify.py. */
extern "C" {
int FUN_0013b820();
void igObject_Destroy(void *);
}
struct It { int a, b, c; };
struct Ar { int w0; unsigned refs; int w8; int w12; It *f16; };
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v140(int, It *); virtual void d34(); virtual void d35(); virtual void v152(int, It *); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void v240(int *, int, int, int); };
struct Mm : VM { int f4; int f8; unsigned f12; int f16; int f20; };
struct O { int w[3]; Mm *f12; int w2[6]; Ar *f40; Ar *f44; };
extern "C" void FUN_0013e230(O *arg0);
void FUN_0013e230(O *arg0) {
    int sp4C;
    unsigned s0, s1;
    Ar *a0;
    FUN_0013b820();
    if (arg0->f40 != 0 || arg0->f44 != 0) {
        sp4C = *arg0->f12->v100();
        if (arg0->f44 != 0) {
            sp4C = sp4C | 0x400000;
        } else {
            sp4C = sp4C & 0xFFBFFFFF;
        }
        if (arg0->f40 != 0) {
            sp4C = sp4C | 0x800000;
        } else {
            sp4C = sp4C & 0xFF7FFFFF;
        }
        s1 = arg0->f12->f12;
        arg0->f12->v240(&sp4C, s1, arg0->f12->f20, 0);
        s0 = 0;
        if (arg0->f44 != 0) {
            for (; s0 < s1; s0++) {
                arg0->f12->v140(s0, &arg0->f44->f16[s0]);
            }
            a0 = arg0->f44;
            if (a0 != 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7fffff) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->f44 = 0;
        }
        s0 = 0;
        if (arg0->f40 != 0) {
            for (; s0 < s1; s0++) {
                arg0->f12->v152(s0, &arg0->f40->f16[s0]);
            }
            a0 = arg0->f40;
            if (a0 != 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7fffff) == 0) {
                    igObject_Destroy(a0);
                }
            }
            arg0->f40 = 0;
        }
    }
}
