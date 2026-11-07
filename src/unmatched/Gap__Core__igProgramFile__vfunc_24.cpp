extern "C" {
void *FUN_002c4ca0(int);
int FUN_002e30b0(void *, const char *);
int FUN_002eb010(int);
int FUN_00304430(void *, int);
int FUN_00304680();
int StringChunk_ReleaseHeader(int, void *);
int StringPool_Construct(int);
int StringPool_Intern(int, void *);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004ff4f0[4];
extern int DAT_00586f20[4];
}
class R {
public:
    int v;
    R(const R &o) : v(o.v) {}
    bool operator==(const R &o) const { return v == o.v; }
};
extern R DAT_004fb410;
extern R DAT_004fb418;
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual void vX(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual R vX(int); };
struct Rc { int w0; int refs;  };
struct PF { char pad[8]; const char *f8; Rc *f12; };
extern "C" R Gap__Core__igProgramFile__vfunc_24(void *arg1, void *arg2) {
    PF *p = (PF *)arg1;
    int var_v0;
    int s0;
    int *old;
    int *hdr;
    int tok;
    Rc *r;
    int temp_v0;
    ((VA *)arg1)->vX();
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    tok = StringPool_Intern(DAT_00586f20[0], arg2);
    old = (int *)p->f8;
    if (old != 0) {
        hdr = old - 2;
        temp_v0 = old[-1] - 1;
        old[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    p->f8 = (const char *)tok;
    s0 = igObject_GetAllocator(arg1);
    r = p->f12;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)r->refs & 0x7fffffULL) == 0) {
            igObject_Destroy(r);
        }
    }
    p->f12 = (Rc *)FUN_002c4ca0(s0);
    FUN_002e30b0(p->f12, p->f8);
    if (((VB *)p->f12)->vX(4) == DAT_004fb418) {
        FUN_00304430(&DAT_004ff4f0[0], (int)p->f8);
        FUN_00304680();
        return DAT_004fb418;
    }
    return DAT_004fb410;
}
