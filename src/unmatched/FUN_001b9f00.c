#include "dw4/reflected.h"
int FUN_001be190();
int FUN_001d9bb0();
int FUN_001e07a0();
int List_AppendWords();
int FUN_001b9f00(igCompileTraversal *arg0, igAttrSet *arg1) {
    int temp_v0;
    igSorter *temp_s0;
    igAttrList *temp_v1;
    temp_s0 = (igSorter *)arg0->_sorter;
    FUN_001d9bb0(temp_s0, arg0->_attrStack);
    temp_v0 = FUN_001be190(arg1, arg0);
    if (temp_v0 == 0) {
        temp_v1 = (igAttrList *)arg1->_attributes;
        List_AppendWords(*(int *)((char *)(temp_s0->_dlist) + 12), temp_v1->_count, temp_v1->_data);
        return 0;
    }
    if (temp_v0 == 4 || temp_v0 == 1) {
        return 0;
    }
    if (FUN_001e07a0(arg0, arg1) == 2) {
        return 2;
    }
    return 0;
}
