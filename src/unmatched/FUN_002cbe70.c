#include "dw4/reflected.h"
void *FUN_002fc250();
int Memory_GetAllocatorBySelector();
int MetaRefList_AppendRetained();
int igMetaField_FinalizeDescriptor();
void *igMetaObject_CreateInstance();
int igObject_Destroy();
extern int DAT_00586918[4];
extern void * DAT_00586920[4];
extern int DAT_00587040[4];
void FUN_002cbe70(void) {
    void *temp_s0;
    igCompoundMetaField *o;
    int t;

    if (DAT_00586920[0] == 0) {
        DAT_00586920[0] = (void *)(igMetaObject_CreateInstance(DAT_00586918[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_00586920[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            o = (igCompoundMetaField *)DAT_00586920[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = *(int *)((char *)(FUN_002fc250()) + 12) - 1;
            ((igCompoundMetaField *)DAT_00586920[0])->_internalIndex = (short) t;
            igMetaField_FinalizeDescriptor(DAT_00586920[0]);
        }
    }
}
