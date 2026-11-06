typedef struct Obj { int w0; int refs; } Obj;
typedef struct R {
    char p0[20]; int *f20; char p1[8]; void *f28; char p2[0];
} R_unused;
typedef struct Res {
    char p0[20]; int *f20; char p1[8]; void *f32; unsigned char f36; char p2[11]; unsigned char f48; unsigned char f49;
    char p3[15]; unsigned char f65; char p4[98]; int f164; char p5[109]; unsigned char f277; char p6[2]; Obj *f280; Obj *f284; Obj *f288;
} Res;
typedef struct W {
    int w0; int w4; unsigned char f8; char p1[19]; unsigned char f28; char p2[23]; unsigned char f52; char p3[3];
    Obj *f56; Obj *f60; Obj *f64; unsigned char f68; char p4[3]; int f72;
} W;
extern int FUN_002d9130(void *);
extern void *FUN_002c37e0(void *);
extern int FUN_003087a0(Obj **, W *, int);
extern int FUN_00308850(W *, void *);
extern void *FUN_00309640(W *, void *);
extern void *igObject_GetAllocator(W *);
extern int FUN_002eb010(int);
extern int StringPool_Construct(int);
extern int StringPool_Intern(int, int);
extern int StringChunk_ReleaseHeader(int, int *);
extern int igObject_Destroy(void *);
extern int DAT_00586f20[4];
void *FUN_00308fb0(W *arg0, int arg1) {
    Res *volatile sp5C;
    Obj *sp58;
    Res *r;
    Obj *a;
    int *old;
    int pool;
    void *res;

    FUN_003087a0(&sp58, arg0, arg1);
    r = (Res *)sp58;
    if (sp58 != 0) {
        sp58->refs = sp58->refs - 1;
        if (((unsigned long long)((long long)sp58->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(sp58);
        }
    }
    if (r != 0) {
        FUN_002d9130(r);
        return r;
    }
    sp5C = (Res *)FUN_002c37e0(arg0->f56 != 0 ? arg0->f56 : igObject_GetAllocator(arg0));
    sp5C->f36 = arg0->f68;
    sp5C->f164 = arg0->f72;
    sp5C->f65 = arg0->f8;
    a = arg0->f56 != 0 ? arg0->f56 : (Obj *)igObject_GetAllocator(arg0);
    r = sp5C;
    if (a != 0) a->refs = a->refs + 1;
    {
        Obj *o = r->f280;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
    }
    r->f280 = a;
    a = arg0->f60 != 0 ? arg0->f60 : (Obj *)igObject_GetAllocator(arg0);
    r = sp5C;
    if (a != 0) a->refs = a->refs + 1;
    {
        Obj *o = r->f284;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
    }
    r->f284 = a;
    a = arg0->f64 != 0 ? arg0->f64 : (Obj *)igObject_GetAllocator(arg0);
    r = sp5C;
    if (a != 0) a->refs = a->refs + 1;
    {
        Obj *o = r->f288;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
    }
    r->f288 = a;
    if (arg0->f28 == 1) {
        sp5C->f277 = arg0->f52;
    }
    sp5C->f49 = 0;
    sp5C->f48 = 1;
    r = sp5C;
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    pool = StringPool_Intern(DAT_00586f20[0], arg1);
    old = r->f20;
    if (old != 0) {
        int *hd = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    r->f20 = (int *)pool;
    sp5C->f32 = arg0;
    FUN_002d9130(sp5C);
    FUN_00308850(arg0, sp5C);
    res = FUN_00309640(arg0, sp5C);
    {
        Res *u = sp5C;
        if (u != 0) {
            ((Obj *)u)->refs = ((Obj *)u)->refs - 1;
            if (((unsigned long long)((long long)((Obj *)u)->refs << 0x29) >> 0x29) == 0) igObject_Destroy(u);
        }
    }
    return res;
}
