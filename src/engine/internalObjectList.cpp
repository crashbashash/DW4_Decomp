typedef struct PointerList {
    int header[2];
    int *data;
    int count;
} PointerList;

typedef struct RefHeader {
    int vtable;
    unsigned refs;
} RefHeader;

#define REF_COUNT_MASK 0x7fffff

extern "C" {
void *ObjectPointerList_Construct(void *);
void *ObjectPointerList_Init(void *);
void *ObjectPointerList_CopyConstruct(void *, void *);
void ObjectPointerList_Destruct(PointerList *);
void ObjectPointerList_Insert(PointerList *, int, int);
void ObjectPointerList_SetCount(PointerList *, int);
int ObjectPointerList_Append(PointerList *, int);
void ObjectPointerList_SetAt(PointerList *, int, int);
void InternalObjectList_SetCount(PointerList *, int);
void igObject_Destroy(void *);
extern int g_InternalObjectList_vtable[4];

void *InternalObjectList_Construct(PointerList *list) {
    ObjectPointerList_Construct(list);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_Init(PointerList *list) {
    ObjectPointerList_Init(list);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_CopyConstruct(PointerList *list, PointerList *source) {
    ObjectPointerList_CopyConstruct(list, source);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void InternalObjectList_Destruct(PointerList *list){InternalObjectList_SetCount(list,0);ObjectPointerList_Destruct(list);}

void InternalObjectList_InsertRetained(PointerList *list, int index, RefHeader *value) {
    if (value)
        ++value->refs;
    ObjectPointerList_Insert(list, index, (int)value);
}

void InternalObjectList_SetCount(PointerList *list,int count){
    int i=list->count;
    if(count<i){
        i--;
        while(i>=count){
            RefHeader *item=(RefHeader *)list->data[i];
            if(item){--item->refs;if(!(item->refs&0x7fffff))igObject_Destroy(item);}
            i--;
        }
    }
    ObjectPointerList_SetCount(list,count);
}

void MetaRefList_AppendRetained(PointerList *list, RefHeader *value) {
    if (value)
        ++value->refs;
    ObjectPointerList_Append(list, (int)value);
}

void InternalObjectList_SetAtRetained(PointerList *list, int index, RefHeader *value) {
    RefHeader *old;
    if (value)
        ++value->refs;
    old = (RefHeader *)list->data[index];
    if (old) {
        --old->refs;
        if (!(old->refs & REF_COUNT_MASK))
            igObject_Destroy(old);
    }
    ObjectPointerList_SetAt(list, index, (int)value);
}
}
