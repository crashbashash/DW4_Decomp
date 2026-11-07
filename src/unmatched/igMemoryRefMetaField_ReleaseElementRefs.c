#include "dw4/reflected.h"
typedef struct {int vtable;unsigned refs;} RefHeader;
int igObject_IsKindOf(void *,int);
unsigned Memory_GetBufferSize(void *);
void igObject_Destroy(void *);
extern int g_igObjectRefMetaField_metaObject[4];

void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *field,void *object){
    RefHeader **data;
    int n;
    int i;
    RefHeader *value;
    if(!field->_refCounted)return;
    if(!field->_memType)return;
    if(!igObject_IsKindOf((void *)field->_memType,g_igObjectRefMetaField_metaObject[0]))return;
    data=*(RefHeader ***)((char *)object+field->_offset);
    if(!data)return;
    n=Memory_GetBufferSize(data)>>2;
    for(i=0;i<n;i++){
        value=data[i];
        if(value){--value->refs;if(!(value->refs&0x7fffff))igObject_Destroy(value);}
    }
}
