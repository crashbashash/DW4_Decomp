#include "dw4/reflected.h"
struct Ob { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void v10(); };
struct Item { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void v22(int); };
/* matching construct: dummy-virtual view so ->v30() dispatches through the object vtable */
struct Self { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void v30(int); };
extern char DAT_0055f170[];
extern "C" {
int Gap__Gfx__igPsx2VisualContext__vfunc_192(int);
int Gap__Gfx__igPsx2VisualContext__vfunc_193(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_194(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_195(int);
int igObject_IsKindOf(Item *, int);
bool FUN_0013e6e0(igGeometrySetAttr *arg0, int arg1) {
    bool ok;
    int t;
    Item **p;
    Item **end;
    t = Gap__Gfx__igPsx2VisualContext__vfunc_192(arg1);
    if (t < 0) {
        arg0->_renderListState = 0;
        return false;
    }
    Gap__Gfx__igPsx2VisualContext__vfunc_194(arg1, t);
    ok = true;
    p = (Item **)((igGeometryAttrList *)arg0->_geometryAttrList)->_data;
    end = p + ((igGeometryAttrList *)arg0->_geometryAttrList)->_count;
    for (; p < end; p++) {
        if (igObject_IsKindOf(*p, *(int *)DAT_0055f170) == 0) {
            ok = false;
            break;
        }
        (*p)->v22(arg1);
    }
    if ((Gap__Gfx__igPsx2VisualContext__vfunc_195(arg1) & 0xFF) && ok) {
        ((Self *)arg0)->v30(arg1);
        arg0->_renderListHandle = t;
        if (arg0->_renderListState == 2) {
            igGeometryAttr **q = (igGeometryAttr **)((igGeometryAttrList *)arg0->_geometryAttrList)->_data;
            igGeometryAttr **qe = q + ((igGeometryAttrList *)arg0->_geometryAttrList)->_count;
            for (; q < qe; q++) {
                ((Ob *)(*q)->_vertexArray)->v10();
            }
        }
    } else {
        Gap__Gfx__igPsx2VisualContext__vfunc_193(arg1, t);
        arg0->_renderListState = 0;
    }
    return ok;
}
}
