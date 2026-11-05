struct Out { int p[5]; int a; int q[14]; int b; };
struct A { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(Out*); };
struct Ent { int w0; int w4; };
extern "C" {
int FUN_002d6e60(...);
Ent *FUN_0032a100(...);
int FUN_0032a180(...);
int FUN_0032a1b0(...);
Ent *FUN_0032a1e0(...);
int FUN_0032ac70(...);
int FUN_0032ad50(...);
int List_InsertWords(...);
void FUN_0032a260(void);  /* code at 0x32a260, passed by address (was DAT_32a260; docs/engine/function-inventory.md) */
extern int DAT_004ffb08[4];
extern int DAT_004ffb18[4];
extern int DAT_004ffb28[4];
extern int DAT_004ffb38[4];
extern int DAT_004ffb48[4];
extern int DAT_004ffb60[4];
extern int DAT_00587220[4];
void FUN_0032a900(A *arg0, int arg1);
}
void FUN_0032a900(A *arg0, int arg1) {
    Ent *spDC;
    Out out;
    unsigned i;
    unsigned j;
    int s2; int s1; int s0;
    arg0->v23(&out);
    for (i = 0; i < 0x40U; i++) {
        s0 = DAT_00587220[i];
        if (s0 != 0) for (j = 0; j < 0x4000U; j += s1) {
            s2 = FUN_0032ac70(s0, j);
            s1 = FUN_0032ad50(s0, j, 0x4000 - j, s2, 3);
            Ent *e = FUN_0032a1e0(168);
            if (e != 0) e = FUN_0032a100(e);
            spDC = e;
            e->w0 = (i << 26) + (j << 12);
            spDC->w4 = s1 << 12;
            switch (s2) {
            case 0: FUN_0032a180(spDC, &DAT_004ffb08[0]); FUN_0032a1b0(spDC, &DAT_004ffb18[0]); break;
            case 1: FUN_0032a180(spDC, &DAT_004ffb28[0]); FUN_0032a1b0(spDC, &DAT_004ffb18[0]); break;
            case 2: FUN_0032a180(spDC, &DAT_004ffb38[0]); FUN_0032a1b0(spDC, &DAT_004ffb18[0]); break;
            case 3: FUN_0032a180(spDC, &DAT_004ffb48[0]); FUN_0032a1b0(spDC, &DAT_004ffb18[0]); break;
            }
            List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
        }
    }
    if (out.b != -1 && out.a != -1) {
        Ent *e = FUN_0032a1e0(168);
        if (e != 0) e = FUN_0032a100(e);
        spDC = e;
        e->w0 = out.b;
        spDC->w4 = out.a;
        FUN_0032a180(spDC, &DAT_004ffb60[0]);
        FUN_0032a1b0(spDC, &DAT_004ffb18[0]);
        List_InsertWords(arg1, FUN_002d6e60(arg1, &spDC, FUN_0032a260), 1, &spDC);
    }
}
