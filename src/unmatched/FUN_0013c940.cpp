class Q { public:
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
    virtual void d47();
    virtual int getId();
};
class P { public:
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void e11();
    virtual void e12();
    virtual void e13();
    virtual void e14();
    virtual void e15();
    virtual void e16();
    virtual void e17();
    virtual void e18();
    virtual void e19();
    virtual void e20();
    virtual void e21();
    virtual void touch(Q *q);
    char pad[32];
    int f36;
};
struct X { char pad[20]; int f20; };
struct S {
    int p0, p4, p8;
    int mode;
    X *f16;
    int f20;
    P *f24;
    int f28, f32, f36;
    int f40;
    int f44, f48;
};
extern "C" {
int FUN_00169c50(Q*, int, int, int, int, int, int, int, long long);
int FUN_00169e30(Q*, int, int, int, int, int, int);
void FUN_0013c940(S *arg0, Q *arg1) {
    int v;
    if (arg0->f16 != 0) v = arg0->f16->f20;
    else v = arg1->getId();
    switch (arg0->mode) {
    case 1:
        if (arg0->f24->f36 < 0) arg0->f24->touch(arg1);
        FUN_00169c50(arg1, v, arg0->f24->f36, arg0->f28, arg0->f32, arg0->f44, arg0->f48, arg0->f36, (long long)arg0->f40);
        return;
    case 2:
        FUN_00169e30(arg1, v, arg0->f20, arg0->f28, arg0->f32, arg0->f44, arg0->f48);
        break;
    case 0:
        break;
    case 3: case 4:
        break;
    default:
        break;
    }
}
}
