#include "dw4/reflected.h"
struct RefObj { int vt; int rc; };
/* matching construct: dummy-virtual class so ->vX() dispatches through the attribute object's vtable slot */
struct AttrObjView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(void *); char pad[24]; int f28; };
extern "C" {
int FUN_00193540(...);
void *FUN_00131390(...);
void *FUN_00135e20(...);
void *FUN_00138ee0(...);
int FUN_003a7a20(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_0050dfd0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int beAction2FLASHSET_Start(int arg0, beAction2InfoRam *arg1);
}
/* The holder is a template on the kind because the three attribute types are distinct classes,
 * each with its own out-of-line destructor. Its constructor registers the fresh attribute (the
 * protected range starts after the allocation call and covers the list registration); the
 * destructor releases the reference. */
template <int kind> struct AttrRef {
    RefObj *p;
    AttrRef(RefObj *o) { p = o; }
    ~AttrRef() {
        RefObj *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
int beAction2FLASHSET_Start(int arg0, beAction2InfoRam *arg1) {
    beAction2InfoWork *c = (beAction2InfoWork *)arg1->_work;
    int list = ((beModelCtrlNode2 *)arg1->_node)->_overrideAttrList;
    if (c->_colorAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        AttrRef<0> r((RefObj *)FUN_00138ee0(a));
        RefObj *o;
        RefObj *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->rc = o->rc + 1;
        old = (RefObj *)c->_colorAttr;
        if (old != 0) {
            old->rc = old->rc - 1;
            if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        c->_colorAttr = (int)o;
    }
    if (c->_textureStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        AttrRef<1> r((RefObj *)FUN_00131390(a));
        RefObj *o;
        RefObj *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->rc = o->rc + 1;
        old = (RefObj *)c->_textureStateAttr;
        if (old != 0) {
            old->rc = old->rc - 1;
            if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        c->_textureStateAttr = (int)o;
    }
    if (c->_lightingStateAttr == 0) {
        int base = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        AttrRef<2> r((RefObj *)FUN_00135e20(a));
        RefObj *o;
        RefObj *old;
        ObjectList_AppendRetained(list, r.p);
        o = r.p;
        if (o != 0) o->rc = o->rc + 1;
        old = (RefObj *)c->_lightingStateAttr;
        if (old != 0) {
            old->rc = old->rc - 1;
            if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        c->_lightingStateAttr = (int)o;
    }
    struct { int x, y, z, w; } v3;
    FUN_00193540(&v3, 1, ((AttrObjView *)c->_colorAttr)->f28);
    v3.y = 0x3F800000;
    v3.x = 0x3F800000;
    ((AttrObjView *)c->_colorAttr)->vX(&v3);
    ((AttrObjView *)c->_textureStateAttr)->vX(0);
    ((AttrObjView *)c->_lightingStateAttr)->vX(0);
    c->_flashSt0 = 1;
    FUN_003a7a20(arg1, &DAT_0050dfd0[0], 0x03F940AC);
    return 1;
}
