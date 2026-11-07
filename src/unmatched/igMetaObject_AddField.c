#include "dw4/reflected.h"
void *FUN_002fe300();
int InternalObjectList_InsertRetained();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
int igMetaObject_CountTree();

void igMetaObject_AddField(igMetaObject *arg0, void *arg1) {
    int flags;
    int idx;
    char *m;
    int n;
    int i;

    flags = arg0->_validity;
    arg0->_validity = flags & ~4;
    *(char *)((char *)(arg1) + 37) = 1;
    *(int *)((char *)(arg1) + 24) = (int)(arg0);
    igMetaField_FinalizeDescriptor(arg1);
    idx = MetaRefList_AppendRetained(arg0->_metaFields, arg1);
    n = igMetaObject_CountTree(arg0);
    for (i = 1; i < n; i++) {
        m = (char *)FUN_002fe300(arg0, i);
        *(int *)(m + 36) = *(int *)(m + 36) & ~4;
        InternalObjectList_InsertRetained(*(int *)(m + 40), idx, arg1);
    }
}
