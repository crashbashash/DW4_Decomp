/* 0x00303c60 — FUN_00303c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
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
