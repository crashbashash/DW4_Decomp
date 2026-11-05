struct Rc { int w0; int refs; };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); int f4; };
struct S { char p0[8]; Rc *f8; void *f12; };
extern "C" {
void *igObject_AllocateStorage(S *, int);
int igObject_Destroy(Rc *);
int FUN_001abb50(S *arg0, A *arg1);
int FUN_001abb50(S *arg0, A *arg1) {
    int n;
    Rc *r;
    n = arg1->vX();
    if (n == 0 || (arg0->f8 != 0) != 0) {
        return 0;
    }
    if (arg1 != 0) {
        arg1->f4 = arg1->f4 + 1;
    }
    r = arg0->f8;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)r->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(r);
        }
    }
    arg0->f8 = (Rc *)arg1;
    arg0->f12 = igObject_AllocateStorage(arg0, n * 4);
    return 1;
}
}
