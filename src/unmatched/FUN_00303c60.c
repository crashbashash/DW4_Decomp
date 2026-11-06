#include "dw4/reflected.h"
int igRefMetaField_CopyConstruct();
extern int DAT_00532c80[4];
void *FUN_00303c60(igObjectRefMetaField *arg0, void *arg1) {
    igRefMetaField_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00532c80[0]);
    arg0->_poolName = 0;
    arg0->_refCounted = (unsigned char) *(unsigned char *)((char *)(arg1) + 60);
    arg0->_metaObject = (int)((int) *(int *)((char *)(arg1) + 56));
    return arg0;
}
