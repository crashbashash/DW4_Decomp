struct EnvMapAttr { char pad[4]; int f4; };
struct EnvMapAttrState { char pad[12]; int f12; };
class EnvMapAttrOps { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(int); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); virtual void vY(int); };
struct EnvMapAlphaAttr { char pad[28]; unsigned char b28; };
struct EnvMapShaderView {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; EnvMapAttrState *f84; int f88; int f92; int f96; int f100; int f104; char pad5[4]; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
extern "C" {
EnvMapAttr *FUN_0013aec0(...);
EnvMapAttr *FUN_00132810(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern EnvMapAttr *DAT_00562730[4];
extern EnvMapAttr *DAT_00562740[4];
extern EnvMapAttr *DAT_00562758[4];
extern EnvMapAttr *DAT_00562a68[4];
extern EnvMapAttr *DAT_00562b28[4];
extern EnvMapAttr *DAT_00562738[4];
extern EnvMapAttr *DAT_00562a80[4];
extern EnvMapAttr *DAT_00562a98[4];
extern EnvMapAttr *DAT_00562ac8[4];
extern EnvMapAttr *DAT_00562af8[4];
extern EnvMapAttr *DAT_00562b40[4];
void FUN_001e1e70(EnvMapShaderView *arg0);
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
extern "C" void FUN_001e1e70(EnvMapShaderView *arg0) {
    EnvMapRef r60;
    r60.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    EnvMapRef r56;
    r56.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, r60.p);
    ObjectList_AppendRetained(arg0->f68, r56.p);
    EnvMapRef r52;
    r52.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    EnvMapRef r48;
    r48.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, r52.p);
    ObjectList_AppendRetained(arg0->f68, r48.p);
    EnvMapRef r44;
    r44.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    EnvMapRef r40;
    r40.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, r44.p);
    ObjectList_AppendRetained(arg0->f68, r40.p);
    ObjectList_AppendRetained(r60.p, DAT_00562a68[0]);
    ObjectList_AppendRetained(r40.p, DAT_00562a68[0]);
    if (arg0->f36 != 0) {
        ObjectList_AppendRetained(r60.p, DAT_00562730[0]);
        ObjectList_AppendRetained(r40.p, DAT_00562730[0]);
        ObjectList_AppendRetained(r60.p, arg0->f36);
        ObjectList_AppendRetained(r56.p, arg0->f36);
        ObjectList_AppendRetained(r60.p, arg0->f92);
        ObjectList_AppendRetained(r56.p, arg0->f92);
        ObjectList_AppendRetained(r60.p, arg0->f96);
        ObjectList_AppendRetained(r56.p, arg0->f96);
        ObjectList_AppendRetained(r60.p, arg0->f88);
        ObjectList_AppendRetained(r56.p, arg0->f88);
    } else {
        ObjectList_AppendRetained(r52.p, DAT_00562730[0]);
        ObjectList_AppendRetained(r40.p, DAT_00562730[0]);
    }
    arg0->f84->f12 = 0;
    ObjectList_AppendRetained(r52.p, arg0->f84);
    ObjectList_AppendRetained(r40.p, arg0->f84);
    ObjectList_AppendRetained(r52.p, DAT_00562740[0]);
    ObjectList_AppendRetained(r48.p, DAT_00562740[0]);
    ObjectList_AppendRetained(r52.p, arg0->f104);
    ObjectList_AppendRetained(r48.p, arg0->f104);
    ObjectList_AppendRetained(r52.p, arg0->f100);
    ObjectList_AppendRetained(r48.p, arg0->f100);
    ObjectList_AppendRetained(r52.p, DAT_00562b28[0]);
    ObjectList_AppendRetained(r48.p, DAT_00562b28[0]);
    ObjectList_AppendRetained(r52.p, DAT_00562758[0]);
    ObjectList_AppendRetained(r48.p, DAT_00562758[0]);
    ObjectList_AppendRetained(r44.p, arg0->f116);
    ObjectList_AppendRetained(r40.p, arg0->f116);
    ObjectList_AppendRetained(r44.p, DAT_00562738[0]);
    ObjectList_AppendRetained(r40.p, DAT_00562738[0]);
    arg0->f112->vX(8);
    ObjectList_AppendRetained(r44.p, arg0->f112);
    ObjectList_AppendRetained(r40.p, arg0->f112);
    ObjectList_AppendRetained(r44.p, arg0->f80);
    ObjectList_AppendRetained(r40.p, arg0->f80);
    ObjectList_AppendRetained(r44.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(r40.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(r44.p, arg0->f76);
    ObjectList_AppendRetained(r40.p, arg0->f76);
}
