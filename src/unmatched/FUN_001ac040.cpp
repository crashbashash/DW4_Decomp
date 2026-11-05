#include "dw4/reflected.h"
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); };
extern "C" {
int FUN_001ad770(...);
int igObject_Destroy(...);
void FUN_001ac040(igAnimationCombiner *arg0, igAnimationState *arg1);
}
/* matching construct: _animHierarchy/_boneInfoListList/_data/_animationState/_baseState are 4-byte reference fields; the casts give the typed views (no layout effect) */
void FUN_001ac040(igAnimationCombiner *arg0, igAnimationState *arg1) {
    int count = ((VC *)arg0->_animHierarchy)->v96();
    int i;
    for (i = 0; i < count; i++) {
        igAnimationCombinerBoneInfoList *l = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)arg0->_boneInfoListList)->_data)[i];
        int n = l->_count;
        if (n > 0) {
            int j;
            bool found = false;
            for (j = n - 1; j >= 0; j--) {
                igAnimationState *x = (igAnimationState *)((igAnimationCombinerBoneInfo **)l->_data)[j]->_animationState;
                if (x == arg1) {
                    found = true;
                } else if (found) {
                    x->_status = 3;
                }
            }
        }
    }
    arg1->_combineMode = 0;
    {
        igObject *r = (igObject *)arg1->_baseState;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if (((unsigned long long)((long long)*(int *)&r->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    arg1->_baseState = 0;
    FUN_001ad770(arg0);
}
