/* Selector is an igMetaField; the containing object list stores object pointers. */
#include "dw4/reflected.h"
typedef struct {int header[2];void **data;int count;} PointerList;
int igStrCmp(const char *,const char *);
void *ObjectPointerList_FindByStringField(PointerList *list,igMetaField *selector,const char *name){
    int i;int byteOffset;
    for(i=0;i<list->count;i++){
        byteOffset=i*4;
        if(igStrCmp(*(char **)((char *)*(void **)((char *)list->data+byteOffset)+selector->_offset),name)==0)
            return *(void **)((char *)list->data+byteOffset);
    }
    return 0;
}
