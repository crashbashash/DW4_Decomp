namespace Gap {
namespace Attrs {

igSmartPointer<igAttr> igAttrDefaultManager::getSharedDefaultAttr(igMetaObject *meta, int unitID) const
{
    igSmartPointer<igAttr> created = createDefaultAttr(meta, unitID);
    igSmartPointer<igAttr> shared = igAttrPool::getStaticAttrPool()->getSharedAttr(created);
    return shared;
}
}
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

namespace Gap {
namespace Attrs {

/* The pool's shared copy of attr: the first attribute alike to it in its type's list, or a clone
 * added to that list (a new type gets its sorted slot in the meta list with an empty attribute
 * list). The non-sharable test compares the search result with 0, not -1, so attr comes back
 * unshared unless its type is the first entry of the non-sharable list.
 * matching construct: each list pointer is a named local read after its GetMeta call. */
igSmartPointer<igAttr> igAttrPool::getSharedAttr(igSmartPointer<igAttr> attribute)
{
    if (attribute == 0) {
        return igSmartPointer<igAttr>(0, kRetainReference);
    }
    igMetaObject *type = ((igAttr *)attribute.get())->getMeta();
    ::igTDataList<igMetaObject *> *nonSharable = (::igTDataList<igMetaObject *> *)(::igMetaObjectList *)_nonSharableMetaList;
    if (nonSharable->sortedIndex(type)) {
        return attribute;
    }
    igMetaObject *meta = ((igAttr *)attribute.get())->getMeta();
    ::igTDataList<igMetaObject *> *metaList = (::igTDataList<igMetaObject *> *)(::igMetaObjectList *)_metaList;
    int index = metaList->sortedIndex(meta);
    igSmartPointer< ::igAttrList> list((::igAttrList *)0, kRetainReference);
    if (index == -1) {
        igMemoryPoolView *allocator = getMemoryPool();
        list.release();
        list.p = (::igAttrList *)igAttrList::_instantiateFromPool(allocator);
        int at = insertObjectSorted((void *)(::igMetaObjectList *)_metaList, meta);
        insertHeld((void *)(::igAttrListList *)_attributeList, at, HeldWord(list));
    } else {
        list = (::igAttrList *)((igAttrListList *)(::igAttrListList *)_attributeList)->get(index);
    }
    unsigned int count = list->_count;
    for (unsigned int i = 0; i < count; i++) {
        igSmartPointer<igAttr> item(((igAttr **)list->_data)[i], kRetainReference);
        if (((igObject *)item.get())->isAlikeShallow((igObject *)attribute.get())) {
            return item;
        }
    }
    igObjectPointer cloned = igObject_Clone((igObjectDispatchView *)attribute.get(), 0);
    igSmartPointer<igAttr> shared = cloned;
    ((igObjectList *)(::igAttrList *)list.get())->append((igObject *)shared.get());
    return shared;
}
}
}

igSmartPointer<igObject> *igSmartPointer_igAttrList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

namespace Gap {
namespace Attrs {

igAttrPool *igAttrPool::getStaticAttrPool()
{
    int allocator;
    if (g_igAttrPool_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent); allocator = owner; } else { int fallback = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleAttribute); allocator = fallback; }
        g_igAttrPool_instance.release();
        g_igAttrPool_instance.p = (::igAttrPool *)_instantiateFromPool((igMemoryPoolView *)allocator);
    }
    return (igAttrPool *)g_igAttrPool_instance.p;
}

void igAttrPool::userUnregister()
{
    g_igAttrPool_instance.clear();
}

void igAttrPool::userRegister()
{

}
}
}

