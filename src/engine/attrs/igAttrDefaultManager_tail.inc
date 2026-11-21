igObjectPointer Gap__Attrs__igAttrDefaultManager__vfunc_23(DefaultSource *source) {
    igObjectPointer created = source->create();
    igObjectPointer wrapped = igAttrPool_GetSharedAttr(igAttrPool_GetStaticAttrPool(), igObjectPointer(created.get(), kRetainReference));
    return wrapped;
}

/* Inserts word at index of list, which takes its own reference (HeldWord, igSmartPointer.h). */
static inline void insertHeld(void *list, int index, const HeldWord &word) {
    word.retain();
    List_InsertWords((igDataList *)list, index, 1, &word);
}

/* Inserts object into the sorted list at its place and returns that index. */
template <class T> static inline int insertObjectSorted(void *list, T *object) {
    RetainedWord<T> word(object);
    int index = FUN_00142bb0((igObjectList *)list, (igObject *const *)&word);
    List_InsertWords((igDataList *)list, index, 1, &word);
    return index;
}

/* The pool's shared copy of attr: the first attribute alike to it in its type's list, or a clone
 * added to that list (a new type gets its sorted slot in the meta list with an empty attribute
 * list). The non-sharable test compares the search result with 0, not -1, so attr comes back
 * unshared unless its type is the first entry of the non-sharable list.
 * matching construct: each list pointer is a named local read after its GetMeta call. */
igObjectPointer igAttrPool_GetSharedAttr(igAttrPool *pool, igObjectPointer attr) {
    if (attr == 0) {
        return igObjectPointer(0, kRetainReference);
    }
    igMetaObject *type = ((igObjectDispatchView *)attr.get())->GetMeta();
    igTDataList<igMetaObject *> *nonSharable = (igTDataList<igMetaObject *> *)pool->_nonSharableMetaList;
    if (nonSharable->sortedIndex(type)) {
        return attr;
    }
    igMetaObject *meta = ((igObjectDispatchView *)attr.get())->GetMeta();
    igTDataList<igMetaObject *> *metaList = (igTDataList<igMetaObject *> *)pool->_metaList;
    int index = metaList->sortedIndex(meta);
    igSmartPointer<igAttrList> list((igAttrList *)0, kRetainReference);
    if (index == -1) {
        igMemoryPoolView *allocator = ((Gap::Core::igObject *)pool)->getMemoryPool();
        list.release();
        list.p = igAttrList_Create(allocator);
        int at = insertObjectSorted((void *)pool->_metaList, meta);
        insertHeld((void *)pool->_attributeList, at, HeldWord(list));
    } else {
        list = ((igAttrList **)((igAttrListList *)pool->_attributeList)->_data)[index];
    }
    unsigned int count = list->_count;
    for (unsigned int i = 0; i < count; i++) {
        igObjectPointer item(((igObject **)list->_data)[i], kRetainReference);
        if (((Gap::Core::igObject *)(item.get()))->isAlikeShallow((Gap::Core::igObject *)attr.get())) {
            return item;
        }
    }
    igObjectPointer cloned = igObject_Clone((igObjectDispatchView *)attr.get(), 0);
    igObjectPointer shared = cloned;
    ((Gap::Core::igObjectList *)list.get())->append((Gap::Core::igObject *)shared.get());
    return shared;
}

igSmartPointer<igObject> *igSmartPointer_igAttrList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igAttrPool *igAttrPool_GetStaticAttrPool(void) {
    int allocator;
    if (g_igAttrPool_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent); allocator = owner; } else { int fallback = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleAttribute); allocator = fallback; }
        g_igAttrPool_instance.release();
        g_igAttrPool_instance.p = igAttrPool_Create((igMemoryPoolView *)allocator);
    }
    return g_igAttrPool_instance;
}

void igAttrPool_UserUnregister(void) {
    g_igAttrPool_instance.clear();
}

void FUN_0013c170(void) {

}

