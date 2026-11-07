struct EnvMapAttr { char pad[4]; int f4; };
struct EnvMapAttrState { char pad[12]; int f12; };
class EnvMapAttrOps { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(int); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); virtual void vY(int); };
struct EnvMapAlphaAttr { char pad[28]; unsigned char b28; };
struct EnvMapShaderView {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[8]; int f56; char pad3[4]; int f64; int f68;
    int pad4; int f76; int f80; EnvMapAttrState *f84; EnvMapAttrOps *f88; EnvMapAttrOps *f92; int f96; EnvMapAttrOps *f100; EnvMapAttrOps *f104; EnvMapAttrOps *f108; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
extern "C" {
EnvMapAttr *FUN_0013aec0(...);
EnvMapAttr *FUN_00132810(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern EnvMapAttr *DAT_00562730[4];
extern EnvMapAttr *DAT_00562738[4];
extern EnvMapAttr *DAT_00562758[4];
extern EnvMapAttr *DAT_00562a80[4];
extern EnvMapAttr *DAT_00562a98[4];
extern EnvMapAttr *DAT_00562ab0[4];
extern EnvMapAttr *DAT_00562ae0[4];
extern EnvMapAttr *DAT_00562b10[4];
extern EnvMapAttr *DAT_00562b40[4];
extern EnvMapAttr *DAT_00562b58[4];
void FUN_001e22c0(EnvMapShaderView *arg0);
EnvMapAttr *FUN_001325a0(...);
}
struct EnvMapTempRef {
    EnvMapAttr *p;
    EnvMapTempRef(EnvMapAttr *x) : p(x) {}
    ~EnvMapTempRef() {
        if (p) {
            --p->f4;
            if (((unsigned long long)(long long)p->f4 & 0x7fffffULL) == 0)
                igObject_Destroy(p);
        }
    }
};
static inline void assignRef(EnvMapAttrOps *&field, const EnvMapTempRef &r) {
    EnvMapAttr *o = r.p;
    if (o) { o->f4++; }
    EnvMapAttr *old = (EnvMapAttr *)field;
    if (old) {
        --old->f4;
        if (((unsigned long long)(long long)old->f4 & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    field = (EnvMapAttrOps *)o;
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
extern "C" void FUN_001e22c0(EnvMapShaderView *arg0) {
    EnvMapRef a;
    EnvMapRef b;
    if (arg0->f104 == arg0->f88) {
        assignRef(arg0->f104, EnvMapTempRef(FUN_001325a0(igObject_GetAllocator(arg0))));
        arg0->f104->vX(0);
        arg0->f104->vY(arg0->f56);
    }
    a.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    b.p = FUN_0013aec0(igObject_GetAllocator(arg0));
    ObjectList_AppendRetained(arg0->f64, a.p);
    ObjectList_AppendRetained(arg0->f68, b.p);
    arg0->f120->vX(3);
    ObjectList_AppendRetained(a.p, arg0->f120);
    ObjectList_AppendRetained(b.p, arg0->f120);
    ObjectList_AppendRetained(a.p, DAT_00562b40[0]);
    ObjectList_AppendRetained(b.p, DAT_00562b40[0]);
    ObjectList_AppendRetained(a.p, DAT_00562738[0]);
    ObjectList_AppendRetained(b.p, DAT_00562738[0]);
    ObjectList_AppendRetained(a.p, arg0->f116);
    ObjectList_AppendRetained(b.p, arg0->f116);
    ObjectList_AppendRetained(a.p, DAT_00562730[0]);
    ObjectList_AppendRetained(b.p, DAT_00562730[0]);
    ObjectList_AppendRetained(a.p, arg0->f80);
    ObjectList_AppendRetained(b.p, arg0->f80);
    ObjectList_AppendRetained(a.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(b.p, DAT_00562a80[0]);
    ObjectList_AppendRetained(a.p, arg0->f76);
    ObjectList_AppendRetained(b.p, arg0->f76);
    arg0->f84->f12 = 0;
    ObjectList_AppendRetained(a.p, arg0->f84);
    ObjectList_AppendRetained(b.p, arg0->f84);
    arg0->f112->vX(1);
    arg0->f112->vY(0);
    ObjectList_AppendRetained(a.p, arg0->f112);
    ObjectList_AppendRetained(b.p, arg0->f112);
    ObjectList_AppendRetained(a.p, DAT_00562758[0]);
    ObjectList_AppendRetained(b.p, DAT_00562758[0]);
    arg0->f104->d23(1);
    ObjectList_AppendRetained(a.p, arg0->f104);
    ObjectList_AppendRetained(b.p, arg0->f104);
    arg0->f100->d23(1);
    ObjectList_AppendRetained(a.p, arg0->f100);
    ObjectList_AppendRetained(b.p, arg0->f100);
    ObjectList_AppendRetained(a.p, DAT_00562a98[0]);
    ObjectList_AppendRetained(b.p, DAT_00562a98[0]);
    arg0->f108->d23(1);
    ((EnvMapAttrState *)arg0->f108)->f12 = 0;
    ObjectList_AppendRetained(a.p, arg0->f108);
    ObjectList_AppendRetained(b.p, arg0->f108);
    ObjectList_AppendRetained(a.p, DAT_00562b58[0]);
    ObjectList_AppendRetained(b.p, DAT_00562b58[0]);
    ObjectList_AppendRetained(a.p, DAT_00562b10[0]);
    ObjectList_AppendRetained(b.p, DAT_00562b10[0]);
    if (arg0->f36 != 0) {
        ObjectList_AppendRetained(a.p, DAT_00562ab0[0]);
        ObjectList_AppendRetained(b.p, DAT_00562ab0[0]);
        EnvMapRef c;
        c.p = FUN_00132810(igObject_GetAllocator(arg0));
        ((EnvMapAttrOps *)c.p)->d23(2);
        ((EnvMapAttrOps *)c.p)->vY(arg0->f36->f12);
        ObjectList_AppendRetained(a.p, c.p);
        ObjectList_AppendRetained(b.p, c.p);
        arg0->f92->d23(2);
        arg0->f88->d23(2);
        ObjectList_AppendRetained(a.p, arg0->f92);
        ObjectList_AppendRetained(b.p, arg0->f92);
        ObjectList_AppendRetained(a.p, arg0->f88);
        ObjectList_AppendRetained(b.p, arg0->f88);
    } else {
        ObjectList_AppendRetained(a.p, DAT_00562ae0[0]);
        ObjectList_AppendRetained(b.p, DAT_00562ae0[0]);
    }
}
