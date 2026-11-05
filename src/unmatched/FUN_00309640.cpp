extern "C" {
int sprintf(...);
int strlen(...);
extern int DAT_004f9a78[4];
}
struct P {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual void a20();
    virtual void a21();
    virtual void a22();
    virtual void a23();
    virtual void a24();
    virtual void a25();
    virtual void a26();
    virtual int v116(...);
    char pad[16]; int f20; int f24;
};
extern "C" P *FUN_00309640(P *arg0, P *arg1);
P *FUN_00309640(P *arg0, P *arg1) {
    char buf[2048];
    int r;
    if (arg1 == 0) return 0;
    r = 0;
    if (arg0->f20 != 0 && strlen(arg0->f20) != 0) {
        sprintf(buf, &DAT_004f9a78[0], arg0->f20, arg1->f20);
        r = arg1->v116(buf) > 0;
    }
    if (r == 0) {
        if (arg0->f24 != 0 && strlen(arg0->f24) != 0) {
            sprintf(buf, &DAT_004f9a78[0], arg0->f24, arg1->f20);
            r = arg1->v116(buf) > 0;
        }
    }
    if (r == 0) {
        arg1->v116(arg1->f20);
    }
    return arg1;
}
