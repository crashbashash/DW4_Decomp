#include "dw4/igSmartPointer.h"
struct MetaInfo { char pad0[12]; int index; };
class DirEntryView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual MetaInfo *getMeta();
};
struct EntryList : public igObjectList {
    void set(int index, igObject *object) {
        if (object != 0) object->_refCount = object->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igObject **)_data)[index] = object;
        }
    }
};
struct DirFile { char pad0[92]; EntryList *sharedEntries; char pad96[184]; int pool; };
extern "C" {
int igObject_IsKindOf(void *object, int meta);
void ObjectList_ResizeRetained(void *list, int count);
void ObjectList_AppendRetained(void *list, void *object);
EntryList *FUN_002bd680(int pool);
extern int DAT_00585b60[4];
igMemoryDirEntry *Gap__Core__igMemoryDirEntry__vfunc_26(igMemoryDirEntry *self, DirFile *file);
}
static inline EntryList *asEntryList(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00585b60[0]) != 0) return (EntryList *)object;
    return 0;
}

extern "C" igMemoryDirEntry *Gap__Core__igMemoryDirEntry__vfunc_26(igMemoryDirEntry *self, DirFile *file) {
    igSmartPointer<EntryList> lists(file->sharedEntries, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((DirEntryView *)self)->getMeta()->index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained(lists.p, index + 1);
        lists->set(index, 0);
    }
    igSmartPointer<EntryList> entries(asEntryList(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->pool;
        entries.release();
        entries.p = FUN_002bd680(pool);
        lists->set(index, entries.p);
    }
    int i;
    int count = entries->_count;
    self->_index = -1;
    EntryList *list = entries.p;
    for (i = 0; i < count; i++) {
        igMemoryDirEntry *entry = ((igMemoryDirEntry **)list->_data)[i];
        if (entry->_memTypeIndex == self->_memTypeIndex && entry->_memSize == self->_memSize &&
            entry->_refCounted == self->_refCounted && entry->_memoryPoolHandle == self->_memoryPoolHandle &&
            entry->_alignmentTypeIndex == self->_alignmentTypeIndex) {
            return entry;
        }
    }
    ObjectList_AppendRetained(list, self);
    return self;
}
