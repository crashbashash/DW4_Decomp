struct Res { int v; Res() {} };
typedef int (*PF)(int *, void *, ...);
#define VCALL(o, off) (*(PF *)(*(char **)(o) + (off)))
class S;
extern "C" {
Res Gap__Core__igProgramFile__vfunc_24(S *);
int FUN_00304430(...);
int FUN_00304680(...);
int FUN_003209a0(...);
int FUN_00320a20(...);
void *FUN_00320ea0(...);

extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int D_004fb418[4];
extern int DAT_004fdda0[4];
extern int DAT_004fddc0[4];
extern int DAT_004fdde0[4];
extern char GPR_005549b4;
}
class Dev { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();  virtual int v25(void *, int, int); };
struct Rec { int p0; int f4; char p8[8]; int f16; int f20; };
class S {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();  virtual Res v23();
    virtual Res v24(int, int, void *);
    int p4; int f8; Dev *f12;
    unsigned char f16, f17, f18, f19, f20, f21; char p22[26];
    int f48; char p52[10];
    unsigned short f62, f64, f66; int f68; int f72; int f76; int f80;
};
extern "C" void FUN_00320b50(int *arg0, S *arg1) {
    int *pp;
    int a;
    int a1v;
    int c21;
    int a2;
    int v;
    Rec *r;
    unsigned short a1s;

    Res sp4C = Gap__Core__igProgramFile__vfunc_24(arg1);
    a = D_004fb418[0];
    pp = (int *)((int)&sp4C + 0);
    a = D_004fb418[0];
    if (*pp == DAT_004fb418[0]) {
        *arg0 = a;
        return;
    }
    if (arg1->f12->v25(&arg1->f16, 0x34, 1) != 1) {
        FUN_00304430(&DAT_004fdda0[0], arg1->f8);
        FUN_00304680();
        Res sp48 = arg1->v23();
        *arg0 = DAT_004fb418[0];
        return;
    }
    a1v = 1;
    c21 = arg1->f21;
    if (GPR_005549b4 == 0x12) {
        a1v = 2;
    }
    if (c21 != a1v) {
        FUN_003209a0(&arg1->f16, a1v);
    }
    if (arg1->f16 != 0x7F || arg1->f17 != 0x45 || arg1->f18 != 0x4C || arg1->f19 != 0x46) {
        FUN_00304430(&DAT_004fddc0[0], arg1->f8);
        FUN_00304680();
        Res sp44 = arg1->v23();
        *arg0 = DAT_004fb418[0];
        return;
    }
    a2 = arg1->f48;
    if (a2 == 0) {
        FUN_00304430(&DAT_004fdde0[0], arg1->f8, a2);
        FUN_00304680();
        Res sp40 = arg1->v23();
        *arg0 = DAT_004fb418[0];
        return;
    }
    Res sp3C = arg1->v24(a2, arg1->f64 * arg1->f62, &arg1->f80);
    a = D_004fb418[0];
    pp = (int *)((int)&sp3C + 0);
    a = D_004fb418[0];
    if (*pp == DAT_004fb418[0]) {
        *arg0 = a;
        return;
    }
    if (GPR_005549b4 == 0x12) {
        v = 2;
    } else {
        v = 1;
    }
    if (arg1->f21 != v) {
        FUN_00320a20(arg1->f80, arg1->f64);
    }
    arg1->f76 = arg1->f64;
    a1s = arg1->f66;
    if (a1s != 0) {
        r = (Rec *)FUN_00320ea0(arg1, a1s);
        if (r != 0 && r->f4 == 3) {
            arg1->f68 = r->f20;
            Res sp38 = arg1->v24(r->f16, r->f20, &arg1->f72);
            a = D_004fb418[0];
            pp = (int *)((int)&sp38 + 0);
    a = D_004fb418[0];
    if (*pp == DAT_004fb418[0]) {
                *arg0 = a;
                return;
            }
        }
    }
    *arg0 = DAT_004fb410[0];
}
