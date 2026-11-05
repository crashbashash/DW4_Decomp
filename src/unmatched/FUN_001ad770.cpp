#include "dw4/reflected.h"
extern "C" void FUN_001ad770(igAnimationCombiner *a);
void FUN_001ad770(igAnimationCombiner *a) {
    int n = ((igAnimationCombinerBoneInfoListList *)a->_boneInfoListList)->_count;
    int i = 0;
    goto cond;
body:
    {
        igAnimationCombinerBoneInfoList *l = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)a->_boneInfoListList)->_data)[i];
        int j = l->_count - 1;
        bool found = 0;
        goto jcond;
jbody:
        if (((igAnimationState *)((igAnimationCombinerBoneInfo **)l->_data)[j]->_animationState)->_combineMode == 0) {
            igIntList *s = (igIntList *)a->_boneInfoListBase;
            if (s->_count != 0 && i >= 0 && i < s->_count) ((int *)s->_data)[i] = j;
            a->_cacheValid = 0;
            found = 1;
            goto jdone;
        }
        j--;
jcond:
        if (j > 0) goto jbody;
jdone:
        if (!found) {
            igIntList *s = (igIntList *)a->_boneInfoListBase;
            if (s->_count != 0 && i >= 0 && i < s->_count) ((int *)s->_data)[i] = 0;
            a->_cacheValid = 0;
        }
        i++;
    }
cond:
    if (i < n) goto body;
}
