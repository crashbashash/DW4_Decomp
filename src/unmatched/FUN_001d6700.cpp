#include "dw4/igSmartPointer.h"

extern "C" {
struct ChildOwner { char pad[20]; int f20; };
struct ChildObject : public igObject { };
int FUN_001d6790(...);
ChildObject *FUN_002c72c0(...);
int FUN_002d8620(...);
int igObject_GetAllocator(...);

void FUN_001d6700(ChildOwner *self) {
    igSmartPointer<ChildObject> created(FUN_002c72c0(igObject_GetAllocator(self)));
    FUN_002d8620(created.get(), self->f20, 0, 0);
    FUN_001d6790(self, created.get());
}
}
