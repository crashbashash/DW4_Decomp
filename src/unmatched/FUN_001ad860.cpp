/* Nested walk releasing a back reference; the found-flag is a bool; locals declared in the order
 * the allocator needs; alternate compiler. */
#include "dw4/reflected.h"
extern "C" { int igObject_Destroy(...); }
/* hypothesis: igAnimationCombiner._animHierarchy (+12, inherited from igAnimationSystem) is a vtable-carrying object whose slot 24 (+96) returns the bone count; its class is not reflected here, so the call goes through this local virtual-dispatch shim */
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };

/* matching construct: the reflected reference fields are 4-byte ints; the casts give the typed views (no layout effect) */
extern "C" int FUN_001ad860(igAnimationCombiner *arg0, igAnimationState *arg1);
int FUN_001ad860(igAnimationCombiner *arg0, igAnimationState *arg1) {
    int var_s4;
    igAnimationCombinerBoneInfoList *temp_s3;
    int var_s2;
    bool var_s1;
    igAnimationState *temp_s0;
    int temp_s7;
    int temp_v0;
    igAnimationState *temp_a0_2;
    temp_s7 = ((V *)arg0->_animHierarchy)->vX();
    var_s4 = 0;
    while (var_s4 < temp_s7) {
        temp_s3 = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)arg0->_boneInfoListList)->_data)[var_s4];
        temp_v0 = temp_s3->_count;
        var_s2 = temp_v0 - 1;
        if (temp_v0 > 0) {
            var_s1 = 0;
            while (var_s2 >= 0) {
                temp_s0 = (igAnimationState *)((igAnimationCombinerBoneInfo **)temp_s3->_data)[var_s2]->_animationState;
                if (temp_s0 == arg1) {
                    var_s1 = true;
                } else if (var_s1) {
                    temp_a0_2 = (igAnimationState *)temp_s0->_cycleMatchTargetState;
                    if (temp_a0_2 == arg1) {
                        if (temp_a0_2 != 0) {
                            temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
                            if (((unsigned long long) ((long long) (int)temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
                                igObject_Destroy(temp_a0_2);
                            }
                        }
                        temp_s0->_cycleMatchTargetState = 0;
                    }
                }
                var_s2 -= 1;
            }
        }
        var_s4 += 1;
    }
    return 1;
}
