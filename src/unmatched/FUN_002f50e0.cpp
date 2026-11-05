/* 0x002f50e0 - FUN_002f50e0. Entity manager teardown: virtual hooks (slots 47, 53, 64, 51), then a descending sweep over 46 slots of 144 bytes (the skip list 6/5/4/0 is a switch, which leaves the compare-chain delay slots empty) and a second, dead loop kept as retail has it. Alternate compiler -O3. */
extern "C" {
int FUN_002f00f0(int);
extern char *DAT_00586dc8[4];
extern void *DAT_00586fd0[4];
}
struct Cnt { int pad[11]; int count; };
struct Sub {
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
    virtual struct Cnt * f20();
};
struct Mgr {
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
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void f47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void f51(int);
    virtual void d52();
    virtual void f53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void f64(int);
};
extern "C" void FUN_002f50e0(Mgr *arg0) {
    int s0;
    Sub *p;
    Cnt *c;
    arg0->f47();
    if ((void *)arg0 == DAT_00586fd0[0]) {
        FUN_002f00f0(0);
    }
    arg0->f53();
    if (*(unsigned char *)(DAT_00586dc8[0] + 119) != 0) {
        arg0->f64(0);
    }
    s0 = 45;
    do {
        p = *(Sub **)((char *)arg0 + s0 * 144 + 20);
        switch (s0) {
        case 0: case 4: case 5: case 6:
            break;
        default:
            if (p != 0) {
                arg0->f51(s0);
            }
        }
        s0--;
    } while (s0 >= 0);
    while (s0 >= 0) {
        p = *(Sub **)((char *)arg0 + s0 * 144 + 20);
        if (p != 0) {
            c = p->f20();
            c->count = c->count - 1;
        }
        s0--;
    }
}
