#include "dw4/igSmartPointer.h"
extern "C" {
int igObject_GetAllocator(void *);
}
struct Entry : igObject { int a; int b; igObject *value; };
extern "C" {
Entry *FUN_0044dc20(int);
int ObjectList_AppendRetained(int, Entry *);
}
struct AttrEntryOwner { char pad[8]; int entries; };

static inline void assign(igObject **slot, igObject *value) {
    igObject *old;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    old = *slot;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = value;
}
extern "C" void FUN_004573f0(AttrEntryOwner *owner, int a, int b, igObject *value) {
    igSmartPointer<Entry> entry(FUN_0044dc20(igObject_GetAllocator(owner)));
    entry->a = a;
    entry->b = b;
    assign(&entry->value, value);
    ObjectList_AppendRetained(owner->entries, entry);
}
