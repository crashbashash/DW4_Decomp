/* spAC is a volatile stack word read once into a local, and the first count read is volatile so
 * the increment reloads it. */
#include "dw4/reflected.h"
int FUN_001b0440();
int igAttrStackManager_MarkStackChanged();
int igTraversal_TraverseChildren();
int List_AppendWords();
int List_Resize();

typedef int (*CB)(void *, int, void *);

int FUN_001b9320(igCompileTraversal *arg0, igAttrSet *arg1) {
    igAttr *a0;
    igAttr *a3;
    int ix;
    igAttr **dp;
    igAttr *ob;
    igAttr *a2;
    CB temp_a2_2;
    igAttr * volatile spAC;
    igAttr **temp_s8;
    int temp_s7;
    int temp_s5;
    igAttrStackManager *temp_s4;
    igAttr **var_s3;
    int temp_s2_2;
    int temp_s2;
    igAttrStack *temp_s1_2;
    igAttrList *temp_s1;
    igAttr **temp_s0_2;
    igAttrStack *temp_s0;

    temp_s1 = (igAttrList *)arg1->_attributes;
    temp_s4 = (igAttrStackManager *)arg0->_attrStack;
    var_s3 = (igAttr **)temp_s1->_data;
    temp_s8 = var_s3 + temp_s1->_count;
    for (; var_s3 < temp_s8; var_s3++) {
        a2 = *var_s3;
        temp_s7 = a2->_cachedUnitID + ((int *)temp_s4->_attrStackIndexTable)[a2->_cachedAttrIndex];
        temp_s0 = ((igAttrStack **)((igAttrStackList *)temp_s4->_attrStacks)->_data)[temp_s7];
        spAC = a2;
        temp_s2 = *(volatile int *)&temp_s0->_count;
        if (temp_s2 < temp_s0->_capacity) {
            temp_s0->_count = temp_s0->_count + 1;
        } else {
            List_Resize(temp_s0, temp_s2 + 1, 4);
        }
        a3 = spAC;
        ((igAttr **)temp_s0->_data)[temp_s2] = a3;
        igAttrStackManager_MarkStackChanged(temp_s4, temp_s0, temp_s7, a3);
    }
    if (arg1->_trigger != 0) {
        FUN_001b0440((igAttrStackManager *)arg0->_attrStack, (igObjectList *)arg0->_flushedAttrs);
        List_AppendWords(*(int *)((char *)((igSorter *)arg0->_sorter)->_dlist + 12), ((igObjectList *)arg0->_flushedAttrs)->_count, ((igObjectList *)arg0->_flushedAttrs)->_data);
    }
    temp_s5 = igTraversal_TraverseChildren(arg0, arg1);
    if (var_s3 != 0) {
        temp_s0_2 = (igAttr **)temp_s1->_data;
        for (var_s3 = var_s3 - 1; var_s3 >= temp_s0_2; var_s3--) {
            a0 = *var_s3;
            temp_s2_2 = a0->_cachedUnitID + ((int *)temp_s4->_attrStackIndexTable)[a0->_cachedAttrIndex];
            temp_s1_2 = ((igAttrStack **)((igAttrStackList *)temp_s4->_attrStacks)->_data)[temp_s2_2];
            ix = temp_s1_2->_count - 1;
            dp = (igAttr **)temp_s1_2->_data;
            temp_a2_2 = (CB)temp_s1_2->_popProc;
            ob = dp[ix];
            if (temp_a2_2 != 0) {
                temp_a2_2(ob, temp_s4->_popProcData, temp_a2_2);
            }
            temp_s1_2->_count = temp_s1_2->_count - 1;
            igAttrStackManager_MarkStackChanged(temp_s4, temp_s1_2, temp_s2_2);
        }
    }
    if (temp_s5 == 2) {
        return 2;
    }
    return 0;
}
