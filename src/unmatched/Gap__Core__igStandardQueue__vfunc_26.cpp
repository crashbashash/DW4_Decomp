/* IgStandardQueue vfunc 26 (push with blocking wait): waits while the ring is full, enqueues the
 * value and signals. Alternate -O3. Status results are copied to a local before the compare (gives
 * beq a0,v1); the loop condition is spelled with (x != 0) ^ 1 for the materialised sltu/xori; the
 * clamp is (a < b) ? a : b. */
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
class Q23 { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual S v23(int);
};
class Self { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual unsigned v26();
    virtual int v27();
    int pad0[2];
    Q *q12;
    Q *q16;
    Q *q20;
    unsigned cap;
    unsigned head;
    int pad32;
    int *buf;
    unsigned f40;
};
extern "C" R Gap__Core__igStandardQueue__vfunc_26(Self *self, int val, int block)
{
    unsigned a;
    unsigned b;
    if (self->v27() != 0 && self->v26() > self->f40 && block == 0) {
        return R(DAT_004fb418[0]);
    }
    while (((self->v27() != 0) ^ 1) == 0 && self->v26() > self->f40) {
        Q23 *t = (Q23 *)**(int **)(*(int *)((char *)DAT_005871d0[0] + 8) + 16);
        t->v23(0x05F5E100);
    }
    int c = self->q12->v31(block).Code();
    if (c != DAT_004fb410[0]) {
        return R(DAT_004fb418[0]);
    }
    if (self->v27() != 0) {
        int c2 = self->q16->v31(block).Code();
        if (c2 != DAT_004fb410[0]) {
            return R(DAT_004fb418[0]);
        }
        if (self->v27() != 0) {
            a = self->f40;
            b = self->cap * 2;
            FUN_00328ab0(self, (a < b) ? a : b);
        }
        self->q16->v29();
    }
    self->buf[self->head] = val;
    self->head = (self->head + 1) % self->cap;
    self->q12->v29();
    self->q20->v29();
    return R(DAT_004fb410[0]);
}
