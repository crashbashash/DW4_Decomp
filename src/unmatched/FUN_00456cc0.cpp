struct T { int word0; int references; int f8; char pad12[16]; int f28; };
struct LL { char pad8[8]; int f8; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v140(int, int); };
struct Obj : VC { char pad4[24]; LL *f28; };
struct P { char pad164[164]; T *f164; };
struct W { char pad12[12]; P *f12; char pad16[4]; Obj *f20; };
extern "C" {
int FUN_001c5eb0(T **, void *, int);
int FUN_004578c0(void *, int *);
void igObject_Destroy(T *);
extern int DAT_0058c400[4];
void FUN_00456cc0(W *arg0, T *arg1);
}
void FUN_00456cc0(W *arg0, T *arg1) {
    T *sp5C; int sp40[4]; T **p; T *old; int v; LL *l;
    if (arg0->f12->f164 != 0) { arg0->f12->f164->f8 = 0; }
    p = &arg0->f12->f164;
    if (arg1 != 0) { arg1->references = arg1->references + 1; }
    old = *p;
    if (old != 0) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) { igObject_Destroy(old); }
    }
    *p = arg1;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058c400[0];
    FUN_004578c0(arg0->f12, sp40);
    l = arg0->f20->f28;
    if (l != 0) { v = l->f8; } else { v = 0; }
    if (v > 1) {
        FUN_001c5eb0(&sp5C, arg0->f20, 0);
        if (sp5C != 0) {
        --sp5C->references;
        if (((unsigned long long)(long long)sp5C->references & 0x7fffffULL) == 0) { igObject_Destroy(sp5C); }
        }
    }
    if (arg1 != 0) { arg0->f20->v140(0, arg1->f28); }
    if (arg1 != 0) { arg1->f8 = (int)arg0; }
}
