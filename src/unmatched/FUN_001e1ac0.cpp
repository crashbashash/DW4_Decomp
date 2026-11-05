struct X { char pad[4]; int f4; };
struct E { char pad[12]; int f12; };
class VD { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); char pad[0]; };
struct W112 { char pad[28]; unsigned char b28; };
struct S {
    char pad0[36]; int f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; E *f84; int f88; int f92; int f96; char pad5[12]; VD *f112; int f116;
};
extern "C" {
X *FUN_0013aec0(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern X *DAT_00562730[4];
extern X *DAT_00562738[4];
extern X *DAT_00562a68[4];
extern X *DAT_00562a80[4];
void FUN_001e1ac0(S *arg0);
}
struct Ref {
    X *p;
    ~Ref() {
        X *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_001e1ac0(S *arg0) {
    float f;
    unsigned int v;
    Ref sp2C;
    sp2C.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    Ref sp28;
    sp28.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, sp2C.p);
    ObjectList_AppendRetained(arg0->f68, sp28.p);
    Ref sp24;
    sp24.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    Ref sp20;
    sp20.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, sp24.p);
    ObjectList_AppendRetained(arg0->f68, sp20.p);
    ObjectList_AppendRetained(sp2C.p, DAT_00562a68[0]);
    ObjectList_AppendRetained(sp20.p, DAT_00562a68[0]);
    if (arg0->f36 != 0) {
        ObjectList_AppendRetained(sp2C.p, DAT_00562730[0]);
        ObjectList_AppendRetained(sp20.p, DAT_00562730[0]);
        ObjectList_AppendRetained(sp2C.p, arg0->f36);
        ObjectList_AppendRetained(sp28.p, arg0->f36);
        ObjectList_AppendRetained(sp2C.p, arg0->f92);
        ObjectList_AppendRetained(sp28.p, arg0->f92);
        ObjectList_AppendRetained(sp2C.p, arg0->f96);
        ObjectList_AppendRetained(sp28.p, arg0->f96);
        ObjectList_AppendRetained(sp2C.p, arg0->f88);
        ObjectList_AppendRetained(sp28.p, arg0->f88);
    } else {
        ObjectList_AppendRetained(sp24.p, DAT_00562730[0]);
        ObjectList_AppendRetained(sp20.p, DAT_00562730[0]);
    }
    ObjectList_AppendRetained(sp24.p, arg0->f116);
    ObjectList_AppendRetained(sp20.p, arg0->f116);
    ObjectList_AppendRetained(sp24.p, DAT_00562738[0]);
    ObjectList_AppendRetained(sp20.p, DAT_00562738[0]);
    f = arg0->f44;
    if (f != 1.0f) {
        if (!(f <= 1.0f) || f < 0.0f) {
            arg0->f44 = 1.0f;
        }
        arg0->f112->vX(11);
        v = (unsigned int)(128.0f * arg0->f44);
        ((W112 *)arg0->f112)->b28 = (unsigned char)v;
    }
    ObjectList_AppendRetained(sp24.p, arg0->f112);
    ObjectList_AppendRetained(sp20.p, arg0->f112);
    ObjectList_AppendRetained(sp24.p, arg0->f80);
    ObjectList_AppendRetained(sp20.p, arg0->f80);
    ObjectList_AppendRetained(sp24.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(sp20.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(sp24.p, arg0->f76);
    ObjectList_AppendRetained(sp20.p, arg0->f76);
    arg0->f84->f12 = 0;
    ObjectList_AppendRetained(sp24.p, arg0->f84);
    ObjectList_AppendRetained(sp20.p, arg0->f84);
}
