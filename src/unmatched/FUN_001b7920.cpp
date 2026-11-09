#include "dw4/reflected.h"
struct SegmentStackList { char pad8[8]; int _count; int _capacity; igObject **_data; };
extern "C" {
int FUN_0030bfa0(SegmentStackList *, int, void *);
int List_RemoveWordAt(SegmentStackList *, int);
int igObject_Destroy(igObject *);
int strcasecmp(void *, void *);
igObject *FUN_001b7920(igCommonTraversal *self, int name);
}
static inline void removeRetained(SegmentStackList *list, int i) {
    igObject *o = list->_data[i];
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    List_RemoveWordAt(list, i);
    list->_data[list->_count] = 0;
}
igObject *FUN_001b7920(igCommonTraversal *self, int name) {
    int index;
    int last;
    SegmentStackList *stack;
    igObject *top;
    index = FUN_0030bfa0((SegmentStackList *)self->_segmentOverrideNames, name, strcasecmp);
    if (index < 0) {
        return 0;
    }
    stack = ((SegmentStackList **)((SegmentStackList *)self->_segmentOverrideStacks)->_data)[index];
    {
        int i = (*(int const *)&stack->_count) - 1;
        top = stack->_data[i];
    }
    last = stack->_count - 1;
    removeRetained(stack, last);
    if (stack->_count == 0) {
        removeRetained((SegmentStackList *)self->_segmentOverrideNames, index);
        removeRetained((SegmentStackList *)self->_segmentOverrideStacks, index);
    }
    return top;
}
