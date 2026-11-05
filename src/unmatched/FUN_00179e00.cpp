class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void *v52(int); };
extern "C" void igObject_Destroy(void *);
struct O { int p0; int refs; int f8; int f12; };
extern "C" struct Ref { O *p; Ref(O *q) : p(q) {} ~Ref() { O *q = p; if (q != 0) { q->refs = q->refs - 1; if (((unsigned long long)(long long)q->refs & 0x7fffffULL) == 0) igObject_Destroy(q); } } operator O *() { return p; } O *operator->() { return p; } };
struct N { int f0; int f4; int f8; O *f12; char f16; char pad[935]; N *f952; };
struct S { char pad[1552]; N *f1552; };
struct G { char pad[56]; int f56; };
extern "C" {
VC *FUN_00165d00(S *);
O *FUN_002b9500(VC *);
void FUN_0030b3c0(O *, void *);
void FUN_0030b720(O *, int, void *);
void FUN_0030b460(O *, int, int, int);
int FUN_00306360(int, int, int);
int thunk_FUN_003065f0(int, int, void *, void *, int, int);
int thunk_FUN_00306770(int, int, void *, void *, void *, int);
extern int DAT_004c22f0[4];
extern int DAT_004dc870[4];
extern int DAT_004de6a8[4];
extern int DAT_004e07b0[4];
extern int DAT_004e07c8[4];
extern int DAT_004e07d8[4];
extern int DAT_004e07e8[4];
extern G *DAT_00586dc8[4];
void FUN_00179e00(S *arg0);
}
void FUN_00179e00(S *arg0) {
    int s3;
    int s2;
    int idx;
    N *n;
    int a1;
    Ref sp6C(FUN_002b9500(FUN_00165d00(arg0)));
    Ref sp68(FUN_002b9500(FUN_00165d00(arg0)));
    s3 = DAT_00586dc8[0]->f56;
    s2 = 0;
    FUN_0030b3c0(sp6C, DAT_004e07b0);
    FUN_0030b720(sp68, 0, DAT_004de6a8);
    { int y = sp68->f12; int x = sp6C->f12;
    a1 = sp68->f8;
    if (a1 == 0) a1 = DAT_004c22f0[0];
    FUN_0030b460(sp6C, a1, x, y); }
    while ((idx = FUN_00306360(s3, sp6C->f8 == 0 ? DAT_004c22f0[0] : sp6C->f8, 0)) != -1) {
        n = (N *)FUN_00165d00(arg0)->v52(960);
        if (n == 0) break;
        n->f16 = 1;
        n->f0 = s2;
        thunk_FUN_003065f0(s3, idx, DAT_004e07c8, &n->f4, 1, 0);
        thunk_FUN_003065f0(s3, idx, DAT_004e07d8, &n->f8, -1 - n->f4, 0);
        n->f12 = FUN_002b9500(FUN_00165d00(arg0));
        thunk_FUN_00306770(s3, idx, DAT_004e07e8, &n->f12, DAT_004dc870, 0);
        s2 += 1;
        n->f952 = arg0->f1552;
        arg0->f1552 = n;
        FUN_0030b720(sp68, s2, DAT_004de6a8);
        FUN_0030b3c0(sp6C, DAT_004e07b0);
        { int y = sp68->f12; int x = sp6C->f12;
        a1 = sp68->f8;
        if (a1 == 0) a1 = DAT_004c22f0[0];
        FUN_0030b460(sp6C, a1, x, y); }
    }
}
