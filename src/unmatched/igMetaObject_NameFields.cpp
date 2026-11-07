#include "dw4/reflected.h"
struct FieldPointerStorage { int prefix[2]; igMetaField **data; int count; };
extern "C" int igMetaObject_GetFieldCount(igMetaObject *);
extern "C" void igMetaField_Configure(igMetaField *,const char *,igMetaField **,int,igMetaObject *);
extern "C" void igMetaField_FinalizeDescriptor(igMetaField *);
extern "C" void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start){
    int count;
    int row;
    igMetaField *field;
    count=igMetaObject_GetFieldCount(meta);
    row=0;
    for(;start<count;start++,row++){
        field=((FieldPointerStorage *)meta->_metaFields)->data[start];
        igMetaField_Configure(field,names[row],handles[row],offsets[row],meta);
        igMetaField_FinalizeDescriptor(field);
    }
}
