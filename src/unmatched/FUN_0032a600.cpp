struct Out { int p[6]; int a0, b0, a1, b1, a2, b2, a3, b3, a4, b4; int q[5]; };
struct A { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(Out*); };
struct Ent { int w0; int w4; };
extern "C" {
int FUN_002d6e60(...);
Ent *FUN_0032a100(...);
int FUN_0032a180(...);
int FUN_0032a1b0(...);
Ent *FUN_0032a1e0(...);
int List_InsertWords(...);
void FUN_0032a260(void);
extern int DAT_004ffa88[4];
extern int DAT_004ffa98[4];
extern int DAT_004ffaa0[4];
extern int DAT_004ffab0[4];
extern int DAT_004ffad0[4];
extern int DAT_004ffaf0[4];
void FUN_0032a600(A *arg0, int arg1);
}
void FUN_0032a600(A *arg0, int arg1) {
    Ent *spDC;
    Out out;
    int *s1;
    arg0->v23(&out);
    s1 = &out.a0;
    if (*s1 != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b0;
        FUN_0032a180(spDC, &DAT_004ffa88[0]);
        FUN_0032a1b0(spDC, &DAT_004ffa98[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a1;
    if (*s1 != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b1;
        FUN_0032a180(spDC, &DAT_004ffaa0[0]);
        FUN_0032a1b0(spDC, &DAT_004ffa98[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a2;
    if (*s1 != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b2;
        FUN_0032a180(spDC, &DAT_004ffab0[0]);
        FUN_0032a1b0(spDC, &DAT_004ffa98[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a3;
    if (*s1 != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b3;
        FUN_0032a180(spDC, &DAT_004ffad0[0]);
        FUN_0032a1b0(spDC, &DAT_004ffa98[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
    s1 = &out.a4;
    if (*s1 != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = *s1;
        spDC->w4 = out.b4;
        FUN_0032a180(spDC, &DAT_004ffaf0[0]);
        FUN_0032a1b0(spDC, &DAT_004ffa98[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
}
