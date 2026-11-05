/* 0x0045f200 - FUN_0045f200. Classifies an object for a given flag bit: 0 when its virtual slot-22 id equals one of two table ids, 2 when igObject_IsKindOf finds a third; the ids are held in a pointer-typed local so the compare puts the call result first (beq v0,s0); C++ with 20 dummy slots; alternate compiler -O3,p, exceptions off. */
class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); int pad[4]; int f20; };
extern "C" {
int igObject_IsKindOf(X *, int);
extern int DAT_005612b0[4];
extern int DAT_005618e8[4];
extern int DAT_005619f8[4];
int FUN_0045f200(int arg0, X *arg1);
}
int FUN_0045f200(int arg0, X *arg1) {
    int *s0;
    if (arg1->f20 & 1) {
        s0 = (int *)DAT_005612b0[0];
        if ((int *)arg1->v88() == s0 || (s0 = (int *)DAT_005618e8[0], (int *)arg1->v88() == s0)) return 0;
        if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) return 2;
    }
    return 1;
}
