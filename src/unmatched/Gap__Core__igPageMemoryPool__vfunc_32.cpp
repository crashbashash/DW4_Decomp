extern "C" int FUN_003081d0(void *, int, int);
extern int DAT_004ff240[4];
extern int DAT_004ff2a0[4];
extern unsigned char GPR_00554dc0;
extern unsigned char GPR_00554dc4;
class T {
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
    virtual void d27();
    virtual void d28();
    virtual void v29();
    virtual void e30();
    virtual void e31();
    virtual void e32();
    virtual void e33();
    virtual void e34();
    virtual void e35();
    virtual void e36();
    virtual void e37();
    virtual void e38();
    virtual void e39();
    virtual void e40();
    virtual void e41();
    virtual void e42();
    virtual void e43();
    virtual void e44();
    virtual void e45();
    virtual void e46();
    virtual void e47();
    virtual void e48();
    virtual void e49();
    virtual void e50();
    virtual void e51();
    virtual void e52();
    virtual void e53();
    virtual void e54();
    virtual void e55();
    virtual void e56();
    virtual void e57();
    virtual void e58();
    virtual void e59();
    virtual void e60();
    virtual void e61();
    virtual void e62();
    virtual void e63();
    virtual void e64();
    virtual void e65();
    virtual void e66();
    virtual void e67();
    virtual void e68();
    virtual void e69();
    virtual void e70();
    virtual void e71();
    virtual void e72();
    virtual void e73();
    virtual void e74();
    virtual void e75();
    virtual void e76();
    virtual void e77();
    virtual void e78();
    virtual void e79();
    virtual void e80();
    virtual void e81();
    virtual void e82();
    virtual void e83();
    virtual void e84();
    virtual void e85();
    virtual void v86();
    int pad4[5];
    int f24;
    char pad28[60];
    long long f88;
    char pad96[16];
    unsigned char f112;
    char pad113[19];
    int f132;
    int f136;
};
extern "C" void Gap__Core__igPageMemoryPool__vfunc_32(T *t) {
    int r;
    if (t->f112 != 0) {
        if (t->f24 != 0) {
            if (t->f136 >= 3 && GPR_00554dc0 == 0) {
                r = FUN_003081d0(&DAT_004ff240[0], t->f132, t->f24);
                if (r != 1 && r == 2) {
                    GPR_00554dc0 = 1;
                }
            }
            t->v86();
        } else {
            if (t->f88 != 0) {
                if (t->f136 >= 3 && GPR_00554dc4 == 0) {
                    r = FUN_003081d0(&DAT_004ff2a0[0], t->f132, (int)t->f88);
                    if (r != 1 && r == 2) {
                        GPR_00554dc4 = 1;
                    }
                }
                t->v86();
            }
        }
        t->f112 = 0;
        t->v29();
    }
}
