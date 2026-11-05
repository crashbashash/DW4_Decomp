/* 0x003286e0 — Gap__Core__igStandardQueue__vfunc_26. igStandardQueue vfunc 26 (push with blocking wait): waits while the ring is full, enqueues the value and signals. Alternate -O3. Status results are copied to a local before the compare (gives beq a0,v1); the loop condition is spelled with (x != 0) ^ 1 for the materialised sltu/xori; the clamp is (a < b) ? a : b. */
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int *DAT_005871d0[4];
int FUN_00328ab0(void *, unsigned);
}
struct S { int code; inline int Code() { return code; } };
struct R { int v; R() {} R(int x) { v = x; } };
class Q { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual S v29();
    virtual void d30();
    virtual S v31(int);
};
class Self { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual unsigned v26();
    int pad0[2];
    Q *q12;
    Q *q16;
    int pad20[1];
    int f24;
    int pad28[2];
    int f36;
    unsigned f40;
};
extern "C" R Gap__Core__igStandardQueue__vfunc_30(Self *o, unsigned n)
{
    if (n > o->f40 || n < o->v26()) {
        return R(DAT_004fb418[0]);
    }
    if (o->f36 == 0) {
        o->f24 = n;
    } else {
        o->q16->v31(1);
        o->q12->v31(1);
        FUN_00328ab0(o, n);
        o->q12->v29();
        o->q16->v29();
    }
    return R(DAT_004fb410[0]);
}
