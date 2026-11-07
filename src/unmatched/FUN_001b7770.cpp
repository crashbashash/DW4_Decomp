#include "dw4/reflected.h"
extern "C" {
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
igObject *FUN_002b9500(int);
int FUN_0030b3c0(igObject *, int);
int FUN_0030b5c0(igObject *);
int FUN_001b7740(void *, void *);
int List_BinarySearchWords(int, void *, void *);
int FUN_002d6e60(int, void *, void *);
int List_InsertWords(int, int, int, void *);
igObject *FUN_0019cba0(int);
int igObject_Destroy(igObject *);
int ObjectList_AppendRetained(igObject *, int);
extern int DAT_00587038[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
void FUN_001b7770(igCommonTraversal *self, int name, int value);
}
struct SegmentOverrideRef { igObject *p; inline void retain() { if (p != 0) p->_refCount = p->_refCount + 1; } inline void set(igObject *o) { p = o; retain(); } };
void FUN_001b7770(igCommonTraversal *self, int name, int value) {
    SegmentOverrideRef newStackRef;
    igObject *searchKey;
    SegmentOverrideRef insertKey;
    int stacks;
    int index;
    int names;
    igObject *str;
    igObject *stack;
    int pos;
    int al = igObject_GetAllocator(self);
    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587060[0]);
    str = FUN_002b9500(al);
    FUN_0030b3c0(str, name);
    FUN_0030b5c0(str);
    { int first = self->_segmentOverrideNames; searchKey = str;
    index = List_BinarySearchWords(first, &searchKey, FUN_001b7740); }
    if (index < 0) {
        names = self->_segmentOverrideNames;
        insertKey.set(str);
        pos = FUN_002d6e60(names, &insertKey, FUN_001b7740);
        List_InsertWords(names, pos, 1, &insertKey);
        stack = FUN_0019cba0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
        newStackRef.p = stack;
        stacks = self->_segmentOverrideStacks;
        newStackRef.retain();
        List_InsertWords(stacks, pos, 1, &newStackRef);
        stack->_refCount = stack->_refCount - 1;
        if (((unsigned long long)((long long)(int)stack->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(stack);
        }
    } else {
        stack = ((igObject **)((igObjectList *)self->_segmentOverrideStacks)->_data)[index];
    }
    ObjectList_AppendRetained(stack, value);
    str->_refCount = str->_refCount - 1;
    if (((unsigned long long)((long long)(int)str->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(str);
    }
}
