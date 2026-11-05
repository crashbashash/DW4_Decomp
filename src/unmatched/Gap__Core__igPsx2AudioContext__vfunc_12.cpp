extern "C" {
int Gap__Core__igObject__vfunc_10(...);
int igObject_Destroy(...);
struct T { int w0; int refs; };
extern T * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_12(void **arg0);
}
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
void Gap__Core__igPsx2AudioContext__vfunc_12(void **arg0) {
    T *p;
    ((DW4VC_100_0 *)(arg0))->vX();
    p = DAT_0055f5d0[0];
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_0055f5d0[0] = 0;
    Gap__Core__igObject__vfunc_10(arg0);
}
