#include "dw4/reflected.h"
extern "C" {
int FUN_001ce970(void *);
int FUN_0018d2b0(void *, void *, void *);
int FUN_0018d360(void *, void *);
void *FUN_00455510(void *);
int FUN_004578c0(void *, void *);
int igObject_Destroy(void *);
}
extern int DAT_0058c410[4];
extern void *DAT_0058c678[4];
/* vtable-call shim for the intersect traversal (slot 23 = vtable offset 100); not a data layout */
struct VO { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(int); };

/* matching construct: the *Ref fields are 4-byte arena handles in the reflected structs; the casts give the typed views (no layout effect) */
extern "C" void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b) {
    int sp[3];
    igObject *s0 = 0;
    if (b->_rootComponent != 0) {
        float v1[3];
        float v2[3];
        float y, x;
        igObject *t;
        FUN_001ce970((void *)a->_intersectTraversal);
        x = ((float *)b->_mousePosition)[0];
        y = ((float *)b->_mousePosition)[1];
        v2[0] = x; v2[1] = y; v2[2] = -10.0f;
        v1[0] = x; v1[1] = y; v1[2] = 10.0f;
        FUN_0018d2b0((void *)a->_ray, v2, v1);
        FUN_0018d360((void *)a->_ray, &a->_inverseProjectionMatrix);
        a->_impactLength = ((igRay *)a->_ray)->_len;
        a->_hit = 0;
        t = (igObject *)a->_hitPath;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        a->_hitPath = 0;
        DAT_0058c678[0] = a;
        ((VO *)a->_intersectTraversal)->v23(((igGuiComponent *)b->_rootComponent)->_node);
        DAT_0058c678[0] = 0;
        if (a->_hit != 0) {
            s0 = (igObject *)FUN_00455510((void *)a->_hitPath);
        }
    }
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    {
        igObject *t = (igObject *)b->_componentUnderMouse;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    b->_componentUnderMouse = (int)s0;
    sp[0] = 2;
    sp[1] = (int)a;
    sp[2] = DAT_0058c410[0];
    FUN_004578c0(b, sp);
}
