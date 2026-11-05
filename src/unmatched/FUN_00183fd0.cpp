extern "C" {
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181850(int);
int FUN_00181840(int);
void FUN_00183f60(float *, int, int, int, float, float);
void FUN_00182420(float *, int, int, float);
int FUN_00183fc0(int);
void igObject_Destroy(void *);
}
class Ref {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void v116(unsigned, float *);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void v144(unsigned, float *);
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void v212(unsigned, float);
    unsigned refs;
    char pad[16];
    Ref *f24;
};
extern "C" void FUN_0015dae0(Ref *, unsigned, float);
extern "C" void FUN_00183fd0(int n, unsigned i, int base, int stride, Ref *a4, Ref *a5, float f) {
    int p; unsigned end; int x; int x2; int p2;
    float B; float A[3]; float ff;
    ff = f * f;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            Ref *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = a4;
        end = i + n;
        for (; i < end; i++) {
            p = base + i * stride;
            x = FUN_001818b0(p);
            x2 = FUN_001818a0(p);
            FUN_00183f60(A, x, x2, FUN_00183fc0(p), f, ff);
            x = FUN_00181850(p);
            FUN_00182420(&B, x, FUN_00181840(p), f);
            a5->v144(i, A);
            FUN_0015dae0(a5, i, B);
        }
        {
            Ref *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end = i + n;
    for (; i < end; i++) {
        p2 = base + i * stride;
        x = FUN_001818b0(p2);
        x2 = FUN_001818a0(p2);
        FUN_00183f60(A, x, x2, FUN_00183fc0(p2), f, ff);
        x = FUN_00181850(p2);
        FUN_00182420(&B, x, FUN_00181840(p2), f);
        a4->v116(i, A);
        a4->v212(i, B);
    }
}
