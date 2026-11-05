#include "dw4/reflected.h"
class VA {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(void *);
};
class VB {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(int);
};
extern "C" {
int FUN_001904f0(...);
int FUN_001908f0(...);
int FUN_001b0ea0(...);
int FUN_001b1030(...);
int FUN_001b1100(...);
int FUN_001b12f0(...);
int FUN_001b13d0(...);
int FUN_001d3c60(...);
int FUN_001dca40(...);
int FUN_001e07a0(...);
extern igMetaObject *DAT_0055ef50[4];
extern int DAT_00562798[4];
extern int DAT_005627a0[4];
extern int DAT_005627a8[4];
extern int DAT_005627b0[4];
extern int DAT_005627b8[4];
extern int DAT_005627c0[4];
extern int DAT_005627c8[4];
extern int DAT_005627d0[4];
extern int DAT_005627d8[4];
int FUN_00134690();
void FUN_001d3e20(igPlanarShadowShader *arg0, igCommonTraversal *arg1);
}
void FUN_001d3e20(igPlanarShadowShader *arg0, igCommonTraversal *arg1) {
    int sp70[16];
    igAttrStackManager *s1 = (igAttrStackManager *)arg1->_attrStack;
    int i;
    ((VA *)arg0->_shadowColorAttr)->v30(arg0->_shadowColor);
    ((VB *)arg0->_stencilState)->v30(arg0->_shadowUseStencil);
    FUN_001b12f0(s1, DAT_005627a8[0]);
    FUN_001b12f0(s1, DAT_005627b0[0]);
    FUN_001b12f0(s1, DAT_005627b8[0]);
    FUN_001b12f0(s1, arg0->_shadowColorAttr);
    FUN_001b12f0(s1, DAT_005627c8[0]);
    FUN_001b12f0(s1, DAT_005627c0[0]);
    FUN_001b12f0(s1, arg0->_stencilState);
    FUN_001b12f0(s1, DAT_005627d0[0]);
    FUN_001b12f0(s1, DAT_005627d8[0]);
    if (arg0->_shadowUseBlend != 0) {
        FUN_001b12f0(s1, DAT_00562798[0]);
    } else {
        FUN_001b12f0(s1, DAT_005627a0[0]);
    }
    FUN_001d3c60(arg0, arg1);
    for (i = 0; i < ((igDataList *)arg0->_lights)->_count; i++) {
        if (FUN_001b0ea0(s1, ((int *)((igDataList *)arg0->_lights)->_data)[i]) != 0) {
            int *m = (int *)((int *)((igDataList *)arg0->_mvmList)->_data)[i];
            igAttrStack *nd;
            int *s5;
            igObjectPool *pool;
            char *o;
            FUN_001908f0(sp70, arg1->_viewMatInv);
            FUN_001904f0(sp70, sp70, (char *)m + 12);
            FUN_001904f0(sp70, sp70, arg1->_viewMat);
            nd = (igAttrStack *)((int *)((igObjectList *)s1->_attrStacks)->_data)[((int *)s1->_attrStackIndexTable)[DAT_0055ef50[0]->_id]];
            if (nd->_cachedOverride >= 0) {
                s5 = (int *)((int *)nd->_data)[nd->_cachedOverride];
            } else if (nd->_count != 0) {
                int k = nd->_count - 1;
                s5 = (int *)((int *)nd->_data)[k];
            } else {
                s5 = (int *)nd->_default;
            }
            pool = (igObjectPool *)arg1->_projectionMatrixPool;
            if (pool->_freeIndex >= pool->_count) FUN_001dca40(pool, (void *)&FUN_00134690);
            o = (char *)((int *)pool->_data)[pool->_freeIndex++];
            FUN_001904f0(o + 12, sp70, (char *)s5 + 12);
            FUN_001b1030(s1, o);
            FUN_001e07a0(arg1, arg0);
            FUN_001b1100(s1, o);
        }
    }
    if (arg0->_shadowUseBlend != 0) {
        FUN_001b13d0(s1, DAT_00562798[0]);
    } else {
        FUN_001b13d0(s1, DAT_005627a0[0]);
    }
    FUN_001b13d0(s1, DAT_005627d8[0]);
    FUN_001b13d0(s1, DAT_005627d0[0]);
    FUN_001b13d0(s1, arg0->_stencilState);
    FUN_001b13d0(s1, DAT_005627c0[0]);
    FUN_001b13d0(s1, DAT_005627c8[0]);
    FUN_001b13d0(s1, arg0->_shadowColorAttr);
    FUN_001b13d0(s1, DAT_005627b8[0]);
    FUN_001b13d0(s1, DAT_005627b0[0]);
    FUN_001b13d0(s1, DAT_005627a8[0]);
}
