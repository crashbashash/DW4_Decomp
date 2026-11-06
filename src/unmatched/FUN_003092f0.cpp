struct Obj { int w0; int refs; };
struct R4 { int a; };
class VX { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual R4 v24(Obj *, int);  };
struct Item { char pad0[8]; unsigned char f8; char pad9[19]; unsigned char f28; char pad29[3]; VX *f32; char pad36[16]; unsigned char f52; char pad53[3]; Obj *f56; Obj *f60; Obj *f64; unsigned char f68; char pad69[3]; int f72; };
struct Out { char pad0[20]; int *f20; char pad24[8]; Item *f32; unsigned char f36; char pad37[11]; unsigned char f48; unsigned char f49; char pad50[15]; unsigned char f65; char pad66[98]; int f164; char pad168[109]; unsigned char f277; char pad278[2]; Obj *f280; Obj *f284; Obj *f288; };
extern "C" {
void *FUN_002c37e0(...);
int FUN_002d9130(...);
int FUN_002d9330(...);
int FUN_002eb010(...);
int FUN_003087a0(...);
int FUN_00308850(...);
void *FUN_00309640(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int igObject_Destroy(...);
extern int DAT_00586f20[4];
void *FUN_003092f0(Item *arg0, int arg1);
}
struct Mem { Obj *p; ~Mem() {} };
struct ORef { Obj *p; ~ORef() { Obj *q = p; if (q) { q->refs = q->refs - 1; if (((unsigned long long)(long long)p->refs & 0x7fffffULL) == 0) igObject_Destroy(p); } } };
#define REL_O(p) { Obj *q_ = (p); if (q_) { q_->refs = q_->refs - 1; if (((unsigned long long)(long long)q_->refs & 0x7fffffULL) == 0) igObject_Destroy(q_); } }
#define ASSIGN_O(o, fld, val) { Obj *n_ = (val); (o) = (Out *)sp5C.p; if (n_ != 0) n_->refs = n_->refs + 1; REL_O((o)->fld) (o)->fld = n_; }
void *FUN_003092f0(Item *arg0, int arg1) {
    Mem sp5C;
    Obj *sp58;
    R4 sp54;
    Obj *r;
    int v;
    Obj *s3;
    int *old;
    int *hd;
    int c;
    Out *o;
    void *res;
    Obj *t;
    FUN_003087a0(&sp58, arg0, arg1);
    r = sp58;
    if (r != 0) {
        r->refs = r->refs - 1;
        if (((unsigned long long)(long long)sp58->refs & 0x7fffffULL) == 0) igObject_Destroy(sp58);
    }
    if (r != 0) {
        FUN_002d9130(r);
        return r;
    }
    sp5C.p = (Obj *)FUN_002c37e0(arg0->f56);
    ((Out *)sp5C.p)->f36 = arg0->f68;
    ((Out *)sp5C.p)->f164 = arg0->f72;
    ((Out *)sp5C.p)->f65 = arg0->f8;
    s3 = arg0->f56;
    if (s3 != 0) { ASSIGN_O(o, f280, s3) }
    s3 = arg0->f60;
    if (s3 != 0) { ASSIGN_O(o, f284, s3) }
    s3 = arg0->f64;
    if (s3 != 0) { ASSIGN_O(o, f288, s3) }
    if (arg0->f28 == 1) {
        ((Out *)sp5C.p)->f277 = arg0->f52;
        FUN_002d9330(sp5C.p);
    }
    ((Out *)sp5C.p)->f49 = 0;
    ((Out *)sp5C.p)->f48 = 1;
    o = (Out *)sp5C.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    v = StringPool_Intern(DAT_00586f20[0], arg1);
    old = o->f20;
    if (old != 0) {
        hd = old - 2;
        c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    o->f20 = (int *)v;
    ((Out *)sp5C.p)->f32 = arg0;
    FUN_002d9130(sp5C.p);
    FUN_00308850(arg0, sp5C.p);
    if (arg0->f28 == 0) {
        res = FUN_00309640(arg0, sp5C.p);
        REL_O(sp5C.p)
        return res;
    }
    FUN_002d9130(sp5C.p);
    sp54 = arg0->f32->v24(sp5C.p, 1);
    res = sp5C.p;
    REL_O(((Obj *)sp5C.p))
    return res;
}
