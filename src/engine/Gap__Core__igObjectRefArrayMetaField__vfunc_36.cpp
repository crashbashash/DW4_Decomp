extern "C" int FUN_003006a0(void *, void *);
extern "C" int FUN_00302780(void *, void *, int, int);
extern "C" int igObject_Destroy(void *, void *);
class V {
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
    virtual int v19(int);
};
struct R { char pad4[4]; int f4; };
struct S { char pad0[8]; int f8; char pad12[56]; int f68; };
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_36(S *s, char *a1, char *a2) {
    int i = 0;
    while (i < s->f68) {
        int base = s->f8;
        int off = i * 4;
        R *x = *(R **)(a1 + base + off);
        V *y = *(V **)(a2 + base + off);
        if (x == 0 && y == 0) break;
        if (x != 0 && y != 0) {
            FUN_003006a0(x, y);
        } else if (x == 0) {
            FUN_00302780(s, a1, i, y->v19(1));
        } else if (y == 0) {
            x->f4 = x->f4 - 1;
            if (((unsigned long long)((long long)x->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(x, y);
            }
            FUN_00302780(s, a1, i, 0);
        }
        i++;
    }
}
