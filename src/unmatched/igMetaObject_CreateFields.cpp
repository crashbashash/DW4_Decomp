#include "dw4/reflected.h"
struct RefHeader { int vtable; unsigned refs; };
typedef igMetaField *(*FieldFactory)(void *);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" void igMetaObject_AppendField(igMetaObject *,igMetaField *);
extern "C" void igObject_Destroy(void *);
extern "C" void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count){
    int i;
    igMetaField *field;
    for(i=0;i<count;i++){
        field=factories[i](Memory_GetAllocatorBySelector(*(int *)0x587040));
        igMetaObject_AppendField(meta,field);
        --((RefHeader *)field)->refs;
        if(!(((RefHeader *)field)->refs&0x7fffff))igObject_Destroy(field);
    }
}
