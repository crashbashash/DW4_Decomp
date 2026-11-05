extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct S { int code; inline int Code() { return code; } };
struct R { int v; R() {} R(int x) { v = x; } };
class Q33 { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); 
    virtual S v33(int);
};
class Q31 { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); 
    virtual S v31();
};
class Self { public:
    virtual void d0();
    int pad4[3];
    Q31 *q16;
    Q33 *q20;
    unsigned cap;
    int pad28;
    unsigned tail;
    int *buf;
};
extern "C" R Gap__Core__igStandardQueue__vfunc_27(Self *self, int *out, int block)
{
    int c = ((Q33 *)self->q20)->v33(block).Code();
    if (c != DAT_004fb410[0]) {
        return R(DAT_004fb418[0]);
    }
    int c2 = ((Q33 *)self->q16)->v33(block).Code();
    if (c2 != DAT_004fb410[0]) {
        return R(DAT_004fb418[0]);
    }
    *out = self->buf[self->tail];
    self->tail = (self->tail + 1) % self->cap;
    ((Q31 *)self->q16)->v31();
    return R(DAT_004fb410[0]);
}
