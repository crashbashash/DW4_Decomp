/* The loop test is written `((F(x) != 0) ^ 1)`, which materialises the sltu/xori. */
struct Item {
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
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual int test();
};
struct Item2 { char p[12]; Item *f12; };
struct Ctl2 { char p[168]; Item2 *f168; };
struct Ctl { char p[12]; Ctl2 *f12; };
extern "C" Item2 *FUN_00456e10(Ctl *, Item2 *, int);
extern "C" int FUN_004555e0(Item2 *);
extern "C" int FUN_00456c20(Ctl2 *, Item2 *);
extern "C" void FUN_00456eb0(Ctl *arg0, int arg1);
void FUN_00456eb0(Ctl *arg0, int arg1) {
    int ok;
    Item2 *s0;
    ok = 0;
    s0 = arg0->f12->f168;
    if (s0 != 0) {
        ok = s0->f12->test() & 0xFF;
    }
    if (ok == 0) {
        do {
            s0 = FUN_00456e10(arg0, s0, arg1);
            if (s0 == arg0->f12->f168 || s0 == 0) break;
        } while ((FUN_004555e0(s0) != 0) ^ 1);
    }
    FUN_00456c20(arg0->f12, s0);
}
