void *InternalObjectList_Construct(PointerList *list, int extra1) {
    ObjectPointerList_Construct((__internalNonRefCountedObjectList *)list, extra1);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_Init(PointerList *list) {
    ObjectPointerList_Init((PointerList *)list);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_CopyConstruct(PointerList *list, PointerList *source) {
    ObjectPointerList_CopyConstruct((__internalNonRefCountedObjectList *)list, (__internalNonRefCountedObjectList *)source);
    *(int *)list = (int)g_InternalObjectList_vtable;
    return list;
}

void InternalObjectList_Destruct(PointerList *list){InternalObjectList_SetCount(list,0);ObjectPointerList_Destruct((__internalNonRefCountedObjectList *)list);}

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

int MetaRefList_AppendRetained(PointerList *list, RefHeader *value) {
    if (value)
        ++value->refs;
    return ObjectPointerList_Append(list, (int)value);
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

