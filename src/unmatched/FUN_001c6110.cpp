/* Recursive mask propagation through virtual child getters; parameter reused in place for the
 * masked value and the loop counter, accumulator/index/list declared before the call-result copy
 * (regalloc.py suggestion); alternate compiler. */
extern "C" int DAT_0048da58[4];
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v92(); virtual void * v96(int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v112(int, int); virtual void d27(); virtual int v120(); };
struct It { int w[5]; int f20; };
struct Lst { int w[2]; int cnt; int pad; It **arr; };
struct O : VO { int f4[6]; Lst *f28; };
extern "C" void FUN_001c6110(O *arg0, int arg1);
void FUN_001c6110(O *arg0, int arg1) {
    int t1, i;
    Lst *a3;
    int a2, m, s2;
    a2 = ~arg0->v120();
    m = DAT_0048da58[0];
    arg1 = a2 & (arg1 & m);
    if (arg1 != 0) {
        a3 = arg0->f28;
        t1 = 0;
        i = 0;
        while (i < (a3 != 0 ? a3->cnt : 0)) {
            t1 |= a3->arr[i]->f20;
            i++;
        }
        s2 = a2 & (m & (arg1 & ~t1));
        if (s2 != 0) {
            arg0->v112(s2, 0);
            arg1 = 0;
            while (arg1 < arg0->v92()) {
                FUN_001c6110((O *)arg0->v96(arg1), s2);
                arg1++;
            }
        }
    }
}
