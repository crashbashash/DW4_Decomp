/* RefHeader and DefaultPointerView are observed ABI projections, not original C++ declarations. */
#include "dw4/reflected.h"
typedef struct {int vtable;unsigned refs;} RefHeader;
int igObject_IsKindOf(void *,int);
unsigned Memory_GetBufferSize(void *);
void igObject_Destroy(void *);
void Memory_FreeBuffer(void *);
void Memory_FreeOwnedBufferUnchecked(void *);
void *Memory_DuplicateBuffer(void *);
void igMemoryRefMetaField_AddElementRefs(igMemoryRefMetaField *,void *);
void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *,void *);
extern int g_igObjectRefMetaField_metaObject[4];

void igMemoryRefMetaField_DestructValue(igMemoryRefMetaField *field,void *object){
    if(field->_destruct){
        igMemoryRefMetaField_ReleaseElementRefs(field,object);
        Memory_FreeBuffer(*(void **)((char *)object+field->_offset));
        *(void **)((char *)object+field->_offset)=0;
    }
}

void igMemoryRefMetaField_AddElementRefs(igMemoryRefMetaField *field,void *object){
    RefHeader *value;RefHeader **data;int i,n;
    if(!field->_refCounted)return;
    if(!field->_memType)return;
    if(!igObject_IsKindOf((void *)field->_memType,g_igObjectRefMetaField_metaObject[0]))return;
    data=*(RefHeader ***)((char *)object+field->_offset);
    if(!data)return;
    n=Memory_GetBufferSize(data)>>2;
    for(i=0;i<n;i++){value=data[i];if(value)++value->refs;}
}

void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *field,void *object){
    int i,n;RefHeader **data;
    if(!field->_refCounted)return;
    if(!field->_memType)return;
    if(!igObject_IsKindOf((void *)field->_memType,g_igObjectRefMetaField_metaObject[0]))return;
    data=*(RefHeader ***)((char *)object+field->_offset);
    if(!data)return;
    n=Memory_GetBufferSize(data)>>2;
    for(i=0;i<n;i++){
        RefHeader *value=data[i];
        if(value){--value->refs;if(!(value->refs&0x7fffff))igObject_Destroy(value);}
    }
}

void igMemoryRefMetaField_SetToDefault(igMemoryRefMetaField *field,void *object){
    void *value,*result;
    igMemoryRefMetaField_ReleaseElementRefs(field,object);
    if(field->_releaseOnReset){value=*(void **)((char *)object+field->_offset);if(value)Memory_FreeOwnedBufferUnchecked(value);}
    value=*(void **)field->_default;
    result=value?Memory_DuplicateBuffer(value):0;
    *(void **)((char *)object+field->_offset)=result;
    igMemoryRefMetaField_AddElementRefs(field,object);
}
