#include "dw4/reflected.h"
extern "C" {
int FUN_0018d2b0(...);
int FUN_0018d360(...);
int FUN_00192fc0(...);
int FUN_001ce970(...);
int FUN_004578c0(...);
void igObject_Destroy(igObject *);
extern int DAT_004e1058[4];
extern int DAT_0058cb00[4];
}
/* matching construct: dummy virtual slots so v23()/v25() dispatch through the retail vtable offsets (igIntersectTraversal) */
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void v23(int); virtual void d24(); virtual void v25(long long); };
extern igPickMode *DAT_0058d240[4];
extern "C" void FUN_00466b20(igPickMode *arg0);
void FUN_00466b20(igPickMode *arg0) {
    float v[3];
    int sp40[3];
    igViewModel *s0;
    int *s1;
    igObject *a0, *r0;
    s0 = (igViewModel *)arg0->_model;
    igGuiSystemModel *p = (igGuiSystemModel *)((igGuiSystem *)arg0->_guiSystem)->_model;
    float y = *(float *)&p->_mousePosition[1];
    v[0] = *(float *)&p->_mousePosition[0];
    v[1] = y;
    *(int *)&v[2] = 0x3F800000;
    FUN_00192fc0(v, v, arg0->_inverseProjectionMatrix);
    FUN_0018d2b0(arg0->_ray, &DAT_004e1058[0], v);
    FUN_0018d360(arg0->_ray, arg0->_inverseMatrix);
    arg0->_impactLength = ((igRay *)arg0->_ray)->_len;
    arg0->_hit = 0;
    a0 = (igObject *)arg0->_hitPath;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)(int)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(a0);
    }
    arg0->_hitPath = 0;
    FUN_001ce970((VM *)arg0->_intersectTraversal);
    ((VM *)arg0->_intersectTraversal)->v25(s0->_drawTime);
    DAT_0058d240[0] = arg0;
    ((VM *)arg0->_intersectTraversal)->v23(((igViewerParameters *)arg0->_parameters)->_scene);
    DAT_0058d240[0] = 0;
    s1 = &((igViewerParameters *)arg0->_parameters)->_selectedObject;
    r0 = (igObject *)arg0->_hitPath;
    if (r0 != 0) {
        r0->_refCount = r0->_refCount + 1;
    }
    a0 = (igObject *)*s1;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)(int)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(a0);
    }
    *s1 = (int)r0;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058cb00[0];
    FUN_004578c0((igViewerParameters *)arg0->_parameters, sp40);
}
