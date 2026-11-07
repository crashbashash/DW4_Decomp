struct EnvMapAttr { char pad[4]; int f4; };
struct EnvMapAttrState { char pad[12]; int f12; };
class EnvMapAttrOps { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(int); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); virtual void vY(int); };
struct EnvMapAlphaAttr { char pad[28]; unsigned char b28; };
struct EnvMapShaderView {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; EnvMapAttrState *f84; EnvMapAttrOps *f88; EnvMapAttrOps *f92; int f96; char pad5[12]; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
extern "C" {
EnvMapAttr *FUN_0013aec0(...);
EnvMapAttr *FUN_00132810(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern EnvMapAttr *DAT_00562730[4];
extern EnvMapAttr *DAT_00562738[4];
extern EnvMapAttr *DAT_00562a80[4];
extern EnvMapAttr *DAT_00562a98[4];
extern EnvMapAttr *DAT_00562ac8[4];
extern EnvMapAttr *DAT_00562af8[4];
extern EnvMapAttr *DAT_00562b40[4];
void FUN_001e16a0(EnvMapShaderView *arg0);
}
struct EnvMapRef {
    EnvMapAttr *p;
    ~EnvMapRef() {
        EnvMapAttr *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_001e16a0(EnvMapShaderView *arg0) {
    float f;
    unsigned int v;
    EnvMapRef sp2C;
    sp2C.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    EnvMapRef sp28;
    sp28.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, sp2C.p);
    ObjectList_AppendRetained(arg0->f68, sp28.p);
    arg0->f120->vX(2);
    ObjectList_AppendRetained(sp2C.p, arg0->f120);
    ObjectList_AppendRetained(sp28.p, arg0->f120);
    ObjectList_AppendRetained(sp2C.p, DAT_00562b40[0]);
    ObjectList_AppendRetained(sp28.p, DAT_00562b40[0]);
    ObjectList_AppendRetained(sp2C.p, arg0->f116);
    ObjectList_AppendRetained(sp28.p, arg0->f116);
    ObjectList_AppendRetained(sp2C.p, DAT_00562738[0]);
    ObjectList_AppendRetained(sp28.p, DAT_00562738[0]);
    ObjectList_AppendRetained(sp2C.p, arg0->f80);
    ObjectList_AppendRetained(sp28.p, arg0->f80);
    ObjectList_AppendRetained(sp2C.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(sp28.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(sp2C.p, arg0->f76);
    ObjectList_AppendRetained(sp28.p, arg0->f76);
    arg0->f84->f12 = 0;
    ObjectList_AppendRetained(sp2C.p, arg0->f84);
    ObjectList_AppendRetained(sp28.p, arg0->f84);
    f = arg0->f44;
    if (f != 1.0f) {
        if (!(f <= 1.0f) || f < 0.0f) {
            arg0->f44 = 1.0f;
        }
        arg0->f112->vX(11);
        v = (unsigned int)(128.0f * arg0->f44);
        ((EnvMapAlphaAttr *)arg0->f112)->b28 = (unsigned char)v;
    } else {
        arg0->f112->vX(1);
    }
    arg0->f112->vY(0);
    ObjectList_AppendRetained(sp2C.p, arg0->f112);
    ObjectList_AppendRetained(sp28.p, arg0->f112);
    ObjectList_AppendRetained(sp2C.p, DAT_00562af8[0]);
    ObjectList_AppendRetained(sp28.p, DAT_00562af8[0]);
    ObjectList_AppendRetained(sp2C.p, DAT_00562730[0]);
    ObjectList_AppendRetained(sp28.p, DAT_00562730[0]);
    if (arg0->f36 != 0) {
        ObjectList_AppendRetained(sp2C.p, DAT_00562a98[0]);
        ObjectList_AppendRetained(sp28.p, DAT_00562a98[0]);
        EnvMapRef sp24;
        sp24.p = FUN_00132810(igObject_GetAllocator(arg0));
        ((EnvMapAttrOps *)sp24.p)->d23(1);
        ((EnvMapAttrOps *)sp24.p)->vY(arg0->f36->f12);
        ObjectList_AppendRetained(sp2C.p, sp24.p);
        ObjectList_AppendRetained(sp28.p, sp24.p);
        arg0->f92->d23(1);
        arg0->f88->d23(1);
        ObjectList_AppendRetained(sp2C.p, arg0->f92);
        ObjectList_AppendRetained(sp28.p, arg0->f92);
        ObjectList_AppendRetained(sp2C.p, arg0->f88);
        ObjectList_AppendRetained(sp28.p, arg0->f88);
    } else {
        ObjectList_AppendRetained(sp2C.p, DAT_00562ac8[0]);
        ObjectList_AppendRetained(sp28.p, DAT_00562ac8[0]);
    }
}
