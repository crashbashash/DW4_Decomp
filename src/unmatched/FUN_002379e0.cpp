#include "dw4/igSmartPointer.h"

struct MessageFilter : igObject {
    igSmartPointer<igObject> _target;
};

struct FilterList : igObject {
    int _count;
    int _capacity;
    MessageFilter **_data;
};

struct FilterDispatcher : igObject {
    FilterList *_filters;
};

extern "C" {
MessageFilter *FUN_00237990(const FilterDispatcher *self, igObject *target);
void *igObject_GetAllocator(void *self);
MessageFilter *FUN_00231b40(void *allocator);
void ObjectList_AppendRetained(FilterList *list, MessageFilter *object);
}

extern "C" igSmartPointer<MessageFilter> FUN_002379e0(FilterDispatcher *self, igObject *target)
{
    igSmartPointer<MessageFilter> filter(FUN_00237990(self, target), kRetainReference);
    if (filter == 0) {
        void *allocator = igObject_GetAllocator(self);
        filter.release();
        filter.p = FUN_00231b40(allocator);
        filter->_target = target;
        ObjectList_AppendRetained(self->_filters, filter);
    }
    return filter;
}
