#include "dw4/igSmartPointer.h"
struct ObjectList : igObject { int count; int capacity; igObject **data; };
struct Owner { char pad[8]; ObjectList *children; };
extern "C" {
ObjectList *FUN_002bd680(int);
int FUN_002d6f50(Owner *, igObject *, int);
int ObjectList_AppendRetainedList(ObjectList *, ObjectList *);
int igObject_GetAllocator(Owner *);
}

extern "C" void FUN_002d7130(Owner *owner) {
    igSmartPointer<ObjectList> copy(FUN_002bd680(igObject_GetAllocator(owner)));
    ObjectList_AppendRetainedList(copy, owner->children);
    ObjectList *children = owner->children;
    int count = children->count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *child = children->data[i];
        if (child != 0) {
            child->_refCount = child->_refCount - 1;
            if ((child->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(child);
            }
        }
    }
    int end = children->count;
    int j;
    for (j = 0; j < end; j++) {
        children->data[j] = 0;
    }
    children->count = 0;
    for (i = 0; i < copy->count; i++) {
        FUN_002d6f50(owner, copy->data[i], 0);
    }
}
