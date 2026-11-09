#include "dw4/igSmartPointer.h"

class FilterDispatcherSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void dispatch(int message, igObject *filter);
};

extern "C" {
igSmartPointer<igObject> FUN_002379e0(FilterDispatcherSlots *self);
void Gap__Insight__igFilterMessageDispatcher__vfunc_23(FilterDispatcherSlots *self, int message);
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_23(FilterDispatcherSlots *self, int message)
{
    igSmartPointer<igObject> filter = FUN_002379e0(self);

    self->dispatch(message, filter.get());
}
