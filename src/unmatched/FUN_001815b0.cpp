extern "C" {
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00181850(int);
int FUN_00181840(int);
void FUN_00181860(float *, int, int, float);
void FUN_00181810(float *, int, int, float);
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
    virtual void f16();
    virtual void f17();
    virtual void v220(unsigned, float *);
    unsigned refs;
    char pad[16];
    Ref *f24;
};
extern "C" void FUN_0015db00(Ref *, unsigned, float *);
extern "C" void FUN_001815b0(int n, unsigned i, int base, int stride, Ref *a4, Ref *a5, float f) {
    int x; unsigned end; int p; int x2; int p2; float D[2]; float C[2]; float B[2]; float A[3];
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
            FUN_00181860(A, x, FUN_001818a0(p), f);
            x = FUN_00181850(p);
            FUN_00181810(B, x, FUN_00181840(p), f);
            a5->v144(i, A);
            C[0] = B[0]; C[1] = B[1];
            FUN_0015db00(a5, i, C);
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
        x2 = FUN_001818b0(p2);
        FUN_00181860(A, x2, FUN_001818a0(p2), f);
        x2 = FUN_00181850(p2);
        FUN_00181810(B, x2, FUN_00181840(p2), f);
        a4->v116(i, A);
        D[0] = B[0]; D[1] = B[1];
        a4->v220(i, D);
    }
}
