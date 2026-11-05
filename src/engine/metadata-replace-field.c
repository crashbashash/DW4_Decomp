#include "dw4/reflected.h"
void igMetaField_FinalizeDescriptor(igMetaField *);
void InternalObjectList_SetAtRetained(void *,int,igMetaField *);
void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field){
    igMetaField_FinalizeDescriptor(field);
    InternalObjectList_SetAtRetained((void *)meta->_metaFields,index,field);
}
