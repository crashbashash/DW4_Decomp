extern "C" {
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00183fc0(int);
int FUN_00183f60(void *, int, int, int, float, float);
void igObject_Destroy(void *);
}
class IndexedValueWriter {
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
    virtual void v116(unsigned, int *);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void v144(unsigned, int *);
    unsigned refs;
    char pad[16];
    IndexedValueWriter *f24;
};
extern "C" void FUN_00183d70(int n, unsigned i, int base, int stride, IndexedValueWriter *a4, IndexedValueWriter *a5, float f) {
    int sp90[4];
    float f2 = f * f;
    int y2;
    int y;
    unsigned end;
    int p;
    int x2;
    int x;
    unsigned end2;
    int p2;
    if (a5 != 0) {
        if (a4 != 0) ++a4->refs;
        {
            IndexedValueWriter *old = a5->f24;
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
            y = FUN_001818a0(p);
            FUN_00183f60(sp90, x, y, FUN_00183fc0(p), f, f2);
            a5->v144(i, sp90);
        }
        {
            IndexedValueWriter *old = a5->f24;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        a5->f24 = 0;
        return;
    }
    end2 = i + n;
    for (; i < end2; i++) {
        p2 = base + i * stride;
        x2 = FUN_001818b0(p2);
        y2 = FUN_001818a0(p2);
        FUN_00183f60(sp90, x2, y2, FUN_00183fc0(p2), f, f2);
        a4->v116(i, sp90);
    }
}
