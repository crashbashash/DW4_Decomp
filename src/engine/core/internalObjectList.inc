void *InternalObjectList_Construct(__internalObjectList *list, int extra1) {
    ObjectPointerList_Construct((__internalNonRefCountedObjectList *)list, extra1);
    list->_vtable = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_Init(__internalObjectList *list) {
    ObjectPointerList_Init((__internalNonRefCountedObjectList *)list);
    list->_vtable = (int)g_InternalObjectList_vtable;
    return list;
}

void *InternalObjectList_CopyConstruct(__internalObjectList *list, __internalObjectList *source) {
    ObjectPointerList_CopyConstruct((__internalNonRefCountedObjectList *)list, (__internalNonRefCountedObjectList *)source);
    list->_vtable = (int)g_InternalObjectList_vtable;
    return list;
}

void InternalObjectList_Destruct(__internalObjectList *list){InternalObjectList_SetCount(list,0);ObjectPointerList_Destruct((__internalNonRefCountedObjectList *)list);}

void InternalObjectList_InsertRetained(__internalObjectList *list, int index, igObject *value) {
    if (value)
        ++value->_refCount;
    ObjectPointerList_Insert((__internalNonRefCountedObjectList *)list, index, (int)value);
}

void InternalObjectList_SetCount(__internalObjectList *list,int count){
    int i=list->_count;
    if(count<i){
        i--;
        while(i>=count){
            igObject *item=((igObject **)list->_data)[i];
            if(item){--item->_refCount;if(!(item->_refCount&0x7fffff))igObject_Destroy(item);}
            i--;
        }
    }
    ObjectPointerList_SetCount((__internalNonRefCountedObjectList *)list,count);
}

int MetaRefList_AppendRetained(__internalObjectList *list, igObject *value) {
    if (value)
        ++value->_refCount;
    return ObjectPointerList_Append((__internalNonRefCountedObjectList *)list, (int)value);
}

void InternalObjectList_SetAtRetained(__internalObjectList *list, int index, igObject *value) {
    igObject *old;
    if (value)
        ++value->_refCount;
    old = ((igObject **)list->_data)[index];
    if (old) {
        --old->_refCount;
        if (!(old->_refCount & REF_COUNT_MASK))
            igObject_Destroy(old);
    }
    ObjectPointerList_SetAt((__internalNonRefCountedObjectList *)list, index, (int)value);
}

