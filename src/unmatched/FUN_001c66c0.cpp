/* Resolve the scene-node handle (+32) of a named child. With force == 0 and a cached handle (+32) it
 * returns 1 at once. Otherwise it refreshes the parent, drops the old handle, resets the interned
 * label (+36, +40), looks up the child index, reads two attributes of the child (a string and an
 * object-name string) into the stack holders, resolves both and, when their text differs, builds a
 * fresh handle, else it reuses the parent. The handle's own child index goes to +40 and the resolved
 * string to +36. Every return path releases the four stack holders.
 * Matching constructs: sp40/sp44 are RP holders (empty-destructor stack objects stay in memory, so
 * the `sp44 = 0; if (sp44) ++refs` pair is a store then a reload); sp3C/sp38/sp34 are the
 * address-taken out-parameter temporaries, released through their own memory slot (REL_TMP, re-read
 * after the decrement); a smart-pointer assignment holds the new value in a local (`n`) between the
 * retain and the store; sp40's pointer is read into `o40` before the `a = ...f8` test so the load
 * fills the branch delay slot. */
struct Obj {
    int vt;
    union {
        int w;
        struct { unsigned cnt : 23; unsigned f : 9; } b;
    } u;
    int f8;
};

struct RP { Obj *p; ~RP() {} };

struct Node {
    char pad0[24];
    char *f24;
    Obj *f28;       /* parent handle */
    Obj *f32;       /* resolved handle (reference counted) */
    char *f36;      /* interned label string */
    int f40;
};

extern "C" {
extern int FUN_001c6520(Node *, int);
extern void FUN_001cd150(Obj **, Node *, char *);
extern void FUN_001ce400(Obj **, char *);
extern int FUN_002eb010(int);
extern int FUN_00306360(Obj *, char *, int);
extern unsigned char FUN_00306910(Obj *, int, void *, char **, void *, int);
extern int StringPool_Construct(int);
extern char *StringPool_Intern(int, int);
extern int thunk_FUN_0012a110(int, int);
extern void igObject_Destroy(Obj *);
extern void StringChunk_ReleaseHeader(int, int *);
extern int DAT_00586f20[4];
extern int DAT_004c22f0[4];
extern int DAT_004e4660[4];
extern int DAT_004e4668[4];
extern int DAT_004e4678[4];
extern int DAT_004e4688[4];

}

#define REL_OBJ(o) { Obj *t_ = (o); if (t_ != 0) { t_->u.w = t_->u.w - 1; if (t_->u.b.cnt == 0) igObject_Destroy(t_); } }
#define RET_OBJ(o) { Obj *t_ = (o); if (t_ != 0) t_->u.w = t_->u.w + 1; }
#define REL_TMP(o) { if (o != 0) { o->u.w = o->u.w - 1; if (o->u.b.cnt == 0) igObject_Destroy(o); } }
#define REL_STR(s) { char *t_ = (s); if (t_ != 0) { int *hd_ = (int *)t_ - 2; int c_ = ((int *)t_)[-1] - 1; ((int *)t_)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*hd_, hd_); } }
#define REL_ALL() { REL_OBJ(sp40.p) REL_OBJ(sp44.p) REL_STR(sp48) REL_STR(sp4C) }

extern "C" int FUN_001c66c0(Node *self, int force);
int FUN_001c66c0(Node *self, int force)
{
    char *sp4C;
    char *sp48;
    RP sp44;
    RP sp40;
    Obj *sp3C;
    Obj *sp38;
    Obj *sp34;
    int idx;
    char *s;
    char *t;
    int a;
    int b;

    if (force == 0 && self->f32 != 0) {
        return 1;
    }
    if (FUN_001c6520(self, force) == 0) {
        return 0;
    }
    REL_OBJ(self->f32)
    self->f32 = 0;
    if (DAT_00586f20[0] == 0) {
        int pool = FUN_002eb010(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    s = StringPool_Intern(DAT_00586f20[0], 0);
    REL_STR(self->f36)
    self->f36 = s;
    self->f40 = -1;
    idx = FUN_00306360(self->f28, (char *)&DAT_004e4668[0], 0);
    if (idx < 0) {
        return 0;
    }
    sp4C = 0;
    sp48 = 0;
    {
        unsigned char found = FUN_00306910(self->f28, idx, &DAT_004e4678[0], &sp4C, &DAT_004e4660[0], 0);
        sp44.p = 0;
        RET_OBJ(sp44.p)
        sp40.p = 0;
        RET_OBJ(sp40.p)
        if (!found) {
            t = self->f24;
            if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
            REL_STR(sp4C)
            sp4C = self->f24;
        }
    }
    if (!(FUN_00306910(self->f28, idx, &DAT_004e4688[0], &sp48, &DAT_004e4660[0], 0) & 0xFF)) {
        REL_ALL()
        return 0;
    }
    FUN_001ce400(&sp3C, self->f24);
    {
        Obj *n = sp3C;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(sp40.p)
        sp40.p = n;
    }
    REL_TMP(sp3C)
    FUN_001ce400(&sp38, sp4C);
    {
        Obj *n = sp38;
        if (n != 0) n->u.w = n->u.w + 1;
        REL_OBJ(sp44.p)
        sp44.p = n;
    }
    REL_TMP(sp38)
    if (sp44.p == 0) {
        REL_ALL()
        return 0;
    }
    {
        Obj *o40 = sp40.p;
        a = sp44.p->f8;
        if (a == 0) a = DAT_004c22f0[0];
        b = o40->f8;
        if (b == 0) b = DAT_004c22f0[0];
    }
    if (thunk_FUN_0012a110(a, b) == 0) {
        Obj *par = self->f28;
        if (par != 0) par->u.w = par->u.w + 1;
        REL_OBJ(self->f32)
        self->f32 = par;
    } else {
        FUN_001cd150(&sp34, self, sp4C);
        {
            Obj *n = sp34;
            if (n != 0) n->u.w = n->u.w + 1;
            REL_OBJ(self->f32)
            self->f32 = n;
        }
        REL_TMP(sp34)
        if (self->f32 == 0) {
            REL_ALL()
            return 0;
        }
    }
    self->f40 = FUN_00306360(self->f32, sp48, 0);
    if (self->f40 == -1) {
        REL_OBJ(self->f32)
        self->f32 = 0;
        REL_ALL()
        return 0;
    }
    t = sp4C;
    if (t != 0) ((int *)t)[-1] = ((int *)t)[-1] + 1;
    REL_STR(self->f36)
    self->f36 = sp4C;
    REL_ALL()
    return 1;
}
