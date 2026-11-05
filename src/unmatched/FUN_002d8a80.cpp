struct Ctx { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual int v29(int); };
struct E { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(int); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(int); int rc; int p8; int idx; int f16; int f20; int p24; int f28; char p32[12]; int f44; int p48; char f52; };
struct L { char p0[8]; int count; char p12[53]; unsigned char f65; unsigned char f66; };
extern "C" {
extern int DAT_00586730[4];
int FUN_002d86b0(L*, int);
int FUN_002d7d60(L*, int);
int FUN_002cc2c0();
int FUN_00301000(L*);
E *FUN_002c0d80(int);
void List_InsertWords(L*, int, int, E**);
void FUN_002fecb0(E*, int);
void FUN_002eed00(E*, int);
int Memory_GetBufferSize(int);
int FUN_002fb8d0(int);
int FUN_002f8920(int);
int FUN_002f04f0(int);
Ctx *FUN_002f88d0();
void FUN_002ff820(E*);
int FUN_002d8a80(L *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7) {
    E * volatile spAC;
    E *spA8;
    int s0;
    int s0b;
    int v;
    if (arg2 == 0) return -1;
    s0 = 0;
    if (arg0->count > 0) {
        s0 = FUN_002d86b0(arg0, DAT_00586730[0]);
        if (s0 < arg0->count) { int r = FUN_002d7d60(arg0, s0); if (r == arg2) return -1; }
    }
    if (arg3 == 0) arg3 = FUN_002cc2c0();
    spAC = FUN_002c0d80(FUN_00301000(arg0));
    spAC->idx = s0;
    spA8 = spAC;
    if (spA8) spA8->rc = spA8->rc + 1;
    List_InsertWords(arg0, s0, 1, &spA8);
    if (arg5) FUN_002fecb0(spAC, arg5);
    spAC->f16 = arg6;
    spAC->f20 = 1;
    FUN_002eed00(spAC, arg3);
    spAC->f28 = Memory_GetBufferSize(arg2);
    spAC->f44 = arg4;
    spAC->v21(arg2);
    spAC->f52 = arg7;
    if (arg0->f65) {
        s0b = 0;
        if (arg0->f66 && arg1 && FUN_002fb8d0(arg1)) s0b = FUN_002f8920(FUN_002fb8d0(arg1));
        if (s0b == 0) s0b = FUN_002f04f0(arg2);
        if (s0b) {
            v = FUN_002f88d0()->v29(s0b);
            if (v == 1 || v == 2) v = -1;
            spAC->v27(v);
        }
    }
    {
        E *t = spAC;
        s0 = t->idx;
        if (t) {
            t->rc = t->rc - 1;
            if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) FUN_002ff820(t);
        }
    }
    return s0;
}
}
