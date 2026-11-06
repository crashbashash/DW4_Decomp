#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offset for igGeometryAttr's configure virtual (vtable slot 39) */
class GeomAttrVirtual {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void Configure(int, int, int);
};
extern "C" {
int FUN_00383910(beFont *, igGeometryAttr *, int, unsigned);
int FUN_00455370(int, int);
int FUN_004553e0(int, int);
int igObject_Destroy(igVertexArray *);
void FUN_00383ab0(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3);
}
/* Owning stack reference to the attribute's vertex array (reference count in the low 23 bits of
 * _refCount); released on scope exit. */
class ObjectRef {
public:
    igVertexArray *p;
    ObjectRef(igVertexArray *o) : p(o) {}
    ~ObjectRef() { igVertexArray *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00383ab0(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3) {
    int v;
    unsigned s0;
    igVertexArray *t;
    if (arg3 != 0) {
        v = FUN_004553e0(((int *)((igObjectList *)arg0->_fonts)->_data)[arg0->_fontIdx], arg2);
        s0 = (v + 2) * 3;
    } else {
        v = FUN_00455370(((int *)((igObjectList *)arg0->_fonts)->_data)[arg0->_fontIdx], arg2);
        s0 = v * 3;
    }
    ((GeomAttrVirtual *)arg1)->Configure(3, v, 0);
    {
        ObjectRef va((igVertexArray *)arg1->_vertexArray);
        t = va.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        t = va.p;
        if (t != 0) {
            if (t->_numVerts < s0) {
                goto b8;
            }
        } else {
b8:
            FUN_00383910(arg0, arg1, arg0->_fontIdx, s0);
        }
    }
}
