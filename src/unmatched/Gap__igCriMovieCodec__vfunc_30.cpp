extern "C" {
int igObject_IsKindOf(void *, int);
int FUN_0026cf70(int);
int FUN_00295468(int);
extern int DAT_00587760[4];
}
struct D { char pad[8]; int f8; int pad2; int f16; 
    static inline D *Cast(D *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_00587760[0]) != 0) { return p; }
        return 0;
    }
};
struct A { char pad[24]; int f24; char pad2[48]; int f76; char pad3[16]; D *f96; };
class C { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
 virtual int v108(A *);
 virtual int v112(A *, int);
};
extern "C" int Gap__igCriMovieCodec__vfunc_30(C *arg0, A *arg1) {
    D *s2 = D::Cast(arg1->f96);
    if (s2 != 0) {
        bool b;
        if (arg1->f24 == 2) {
            b = FUN_0026cf70(s2->f16) == 1;
        } else {
            b = FUN_00295468(s2->f8) == 1;
        }
        if (arg1->f76 == 1 && !b) {
            return arg0->v112(arg1, 1);
        }
        if (arg1->f76 == 0 && b) {
            return arg0->v108(arg1);
        }
    }
    return 0;
}
