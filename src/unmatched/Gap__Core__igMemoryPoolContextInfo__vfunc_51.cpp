/* 0x002f2730 - Gap__Core__igMemoryPoolContextInfo__vfunc_51. Context-info entry lookup by index: bounds test, key slot pointer kept, hidden-result virtual 208 when the entry is flagged, else delegate to the previous pool via virtual 92; alternate compiler -O3. Verified byte-identical by tools/verify.py. */
struct R { int a; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v92(int); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual R v208(int); };
struct E { int pad[5]; int key; int val[30]; };
struct Ctx : VC { };
extern "C" { extern VC *DAT_00587000[4]; extern int DAT_00587010[4]; }
extern "C" int Gap__Core__igMemoryPoolContextInfo__vfunc_51(Ctx *arg0, int arg1);
int Gap__Core__igMemoryPoolContextInfo__vfunc_51(Ctx *arg0, int arg1) {
    int i, j;
    int r = 0;
    if (arg1 >= 0 && arg1 < 46) {
        char *e = (char *)(arg1 * 144) + (int)arg0;
        int *pk = (int *)(e + 20);
        r = *pk;
        if (r == 0) {
            if (*(int *)(e + 160) & 0x04000000) {
                arg0->v208(arg1);
                return *pk;
            }
            if (1 < DAT_00587010[0]) {
                for (i = DAT_00587010[0] - 1; i >= 0; i--) {
                    if (DAT_00587000[i] == (VC *)arg0) break;
                }
                j = i - 1;
                if (j >= 0) {
                    VC *p = DAT_00587000[j];
                    if (p != (VC *)arg0) r = p->v92(arg1);
                }
            }
        }
    }
    return r;
}
