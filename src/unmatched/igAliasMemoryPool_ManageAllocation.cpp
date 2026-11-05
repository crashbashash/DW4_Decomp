struct R { int v; R() {} };
class Tk {
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual int v220(long long, unsigned short);
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual int v236(int, long long, unsigned short);
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual int v264(int);
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual R v372(int, void *);
};
class Pool {
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
    virtual int v92(long long, int);
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
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
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual int v336(int);
    int pad4;
    char pad8[105];
    unsigned char f113;
    char pad114[14];
    unsigned long long f128;
    int f136;
    int f140;
    unsigned long long f144;
    char pad152[8];
    unsigned long long f160;
    int f168;
    char pad172[4];
    unsigned short f176;
    char pad178[2];
    Tk *f180;
};
extern "C" {
int igAliasMemoryPool_Lock(...);
int igAliasMemoryPool_Unlock(...);
int igAliasMemoryPool_UnlockAndReturn(...);
R FUN_002f0220(int, Pool *);
R FUN_002f0320(int, Pool *);
int igAliasMemoryPool_ManageAllocation(Pool *arg0, int arg1, long long arg2, unsigned short arg3);
}
extern "C" int igAliasMemoryPool_ManageAllocation(Pool *arg0, int arg1, long long arg2, unsigned short arg3) {
    int s1 = 0;
    long long s0;
    int v0;
    igAliasMemoryPool_Lock(arg0);
    if ((arg3 & 0xFFFF) < arg0->f176) arg3 = arg0->f176;
    s0 = (int)arg2;
    for (;;) {
        if (arg2 == -1) {
            s1 = 0;
            if (arg1 == 0) {
                igAliasMemoryPool_Unlock(arg0);
                return 0;
            }
            { int t = arg0->v336(arg1); arg0->f128 = arg0->f128 - t; }
            arg0->f140 = arg0->f140 + 1;
            if (arg0->f113 != 0) {
                R sp8C = arg0->f180->v372(arg1, arg0->f180);
            } else {
                R sp88 = FUN_002f0320(arg1, arg0);
            }
            arg0->f180->v264(arg1);
            break;
        }
        if (arg0->f128 + s0 > arg0->f144) {
            if (arg0->v92(arg2, 1) == 0) {
                s1 = 0;
                break;
            }
            continue;
        }
        if (arg1 != 0) {
            if (arg0->f180 != 0) {
                if (arg1 != 0) {
                    { int t = arg0->v336(arg1); arg0->f128 = arg0->f128 - t; }
                    arg0->f140 = arg0->f140 + 1;
                }
                if (arg0->f113 != 0) {
                    R sp84 = arg0->f180->v372(arg1, arg0->f180);
                } else {
                    R sp80 = FUN_002f0320(arg1, arg0);
                }
                s1 = arg0->f180->v236(arg1, arg2, arg3);
            }
        } else {
            if (arg0->f180 != 0) {
                s1 = arg0->f180->v220(arg2, arg3);
            }
        }
        if (s1 != 0) {
            arg0->f128 = arg0->f128 + (int)arg2;
            if (arg0->f160 < arg0->f128) arg0->f160 = arg0->f128;
            arg0->f136 = arg0->f136 + 1;
            v0 = arg0->f136 - arg0->f140;
            if (arg0->f168 < v0) arg0->f168 = v0;
            if (arg0->f113 != 0) {
                R sp7C = arg0->f180->v372(s1, arg0);
            } else {
                R sp78 = FUN_002f0220(s1, arg0);
            }
        }
        break;
    }
    return igAliasMemoryPool_UnlockAndReturn(arg0, s1);
}
