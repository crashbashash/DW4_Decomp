#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
/* matching construct: dummy virtual slots so the vX() calls dispatch through the retail vtable offset */
struct DummyVirtualComponent { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(void *); char pad[24]; int f28; };
struct Action2SwitchBits { char pad32[32]; igUnsignedIntList *f32; };
extern "C" {
int FUN_00193540(...);
void *FUN_00135e20(...);
void *FUN_00138ee0(...);
void *FUN_00139600(...);
int FUN_003a7a20(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_004e0858[4];
extern int DAT_0050dfe0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int beAction2FADESET_Start(int arg0, beAction2InfoRam *arg1, beAction2FADESET *arg2);
}
/* Owning stack reference to the freshly created attribute (colour 0, blend state 1, lighting state 2): the
 * exception table protects it from after its construction, and the three out-of-line destructor copies retail
 * keeps are 0x0019ab10, 0x001aaf00 and 0x00239200 (config/SLUS-20836/unit-objects.json duplicates __dt__6Ref<k>Fv). */
template <int kind> struct Ref {
    igObject *p;
    Ref(igObject *o) : p(o) {}
    ~Ref() {
        igObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
/* matching construct: the (igObject *)/(int) casts on _colorAttr/_blendStateAttr/_lightingStateAttr stand in for 4-byte reference fields */
int beAction2FADESET_Start(int arg0, beAction2InfoRam *arg1, beAction2FADESET *arg2) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    int list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
    char *nm = (char *)arg2->_name;
    nm = nm != 0 ? nm : (char *)DAT_004e0858;
    if (*nm == 0x48) {
        unsigned bit;
        unsigned i;
        igUnsignedIntList *l;
        unsigned *p;
        int cnt;
        int v;
        int m;
        /* matching construct: cast from the 4-byte reference field (int) to the typed pointer; no layout effect */
        beAction2Info *pi = (beAction2Info *)arg1->_parentInfo;
        l = ((Action2SwitchBits *)pi->_switch)->f32;
        bit = arg1->_ramNo;
        i = bit >> 5;
        m = 1 << (bit & 0x1F);
        p = (unsigned *)l->_data + i;
        cnt = l->_count;
        v = ~m & *p;
        if (cnt != 0 && (int)i >= 0 && (int)i < cnt) {
            *p = v;
        }
    } else {
    if (c->_colorAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<0> r((igObject *)FUN_00138ee0(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_colorAttr;
        IG_OBJECT_RELEASE(old);
        c->_colorAttr = (int)o;
    }
    if (c->_blendStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<1> r((igObject *)FUN_00139600(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_blendStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_blendStateAttr = (int)o;
    }
    if (c->_lightingStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
                igObject *o;
        igObject *old;
        Ref<2> r((igObject *)FUN_00135e20(a));
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)c->_lightingStateAttr;
        IG_OBJECT_RELEASE(old);
        c->_lightingStateAttr = (int)o;
    }
        char *nm2 = (char *)arg2->_name;
        nm2 = nm2 != 0 ? nm2 : (char *)DAT_004e0858;
        if (*nm2 == 0x49) {
            struct { int x, y, z, w; } v3;
            FUN_00193540(&v3, 1, ((igColorAttr *)c->_colorAttr)->_colorPacked);
            v3.w = 0;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v3);
            ((DummyVirtualComponent *)c->_blendStateAttr)->vX((void *)1);
            ((DummyVirtualComponent *)c->_lightingStateAttr)->vX((void *)0);
            c->_fadeValue = 0.0f;
            c->_fadeLimitValue = arg2->_fadeValue;
            c->_fadeAddValue = arg2->_fadeValue / arg2->_fadeTime;
            c->_fadeSt0 = 1;
        } else {
            struct { int x, y, z; float w; } v3;
            FUN_00193540(&v3, 1, ((igColorAttr *)c->_colorAttr)->_colorPacked);
            v3.w = arg2->_fadeValue;
            ((DummyVirtualComponent *)c->_colorAttr)->vX(&v3);
            ((DummyVirtualComponent *)c->_blendStateAttr)->vX((void *)1);
            ((DummyVirtualComponent *)c->_lightingStateAttr)->vX((void *)0);
            c->_fadeValue = arg2->_fadeValue;
            c->_fadeLimitValue = arg2->_fadeValue;
            c->_fadeAddValue = arg2->_fadeValue / arg2->_fadeTime;
            c->_fadeSt0 = 2;
        }
        FUN_003a7a20(arg1, &DAT_0050dfe0[0], 0);
    }
    return 1;
}
