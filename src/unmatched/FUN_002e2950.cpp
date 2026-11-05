struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(int); virtual void v22(); virtual void v23(void*); int rc; int f8; int f12; int p16; int f20; };
struct Arg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual Obj* v19(int); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(void*); int p4[5]; int f24; int f28; int f32; };
struct G { char p[64]; int f64; };
extern "C" {
Obj *FUN_002c72c0(int);
int FUN_002d8fe0(Obj*, int);
int FUN_003087a0(Obj**, int, int);
int FUN_00308850(int, Obj*);
int ObjectList_AppendRetained(Obj*, Obj*);
int igNamedObject_SetName(Obj*, int);
void igObject_Destroy(Obj*);
int igObject_GetAllocator(Arg*);
extern G *DAT_00586dc8[4];
}
#define REL(p) do { Obj *t_ = (p); if (t_ != 0) { t_->rc = t_->rc - 1; if (((unsigned long long)((long long)t_->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t_); } } while (0)
extern "C" int FUN_002e2950(Arg *arg0, void (*arg1)(Arg *));
int FUN_002e2950(Arg *arg0, void (*arg1)(Arg *)) {
    Obj * volatile sp5C;
    Obj * volatile sp58;
    int s1;
    int s0;
    Obj *t;
    s0 = DAT_00586dc8[0]->f64;
    FUN_003087a0((Obj **)&sp5C, s0, arg0->f28);
    if (sp5C == 0) {
        s1 = igObject_GetAllocator(arg0);
        t = sp5C;
        REL(t);
        sp5C = FUN_002c72c0(s1);
        FUN_002d8fe0(sp5C, arg0->f28);
        FUN_00308850(s0, sp5C);
    }
    sp5C->v23(arg0);
    if (arg0->f24 == 0) arg0->v42((void *)arg1);
    if (arg0->f24 == 0 && arg1 != 0) arg1(arg0);
    if (arg0->f24 != 0) {
        sp58 = arg0->v19(1);
        t = sp58;
        if (t != 0) t->rc = t->rc + 1;
        t = sp58;
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
        igNamedObject_SetName(sp58, arg0->f32);
        sp58->f20 = 0;
        sp58->v21(arg0->f24);
        sp58->f12 = sp5C->f8;
        { Obj *b_ = sp58; Obj *a_ = sp5C; ObjectList_AppendRetained(a_, b_); }
        t = sp58;
        REL(t);
        t = sp5C;
        REL(t);
        return 1;
    }
    t = sp5C;
    REL(t);
    return 0;
}
