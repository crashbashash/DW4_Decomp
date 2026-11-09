#include "dw4/igSmartPointer.h"

struct ObjectSlotOwner {
    char pad[8];
    igObject *slot;
    void setSlot(const igSmartPointer<igObject> &object) {
        igObject *retained = object.get();
        igObject *previous;
        if (retained != 0) {
            retained->_refCount = retained->_refCount + 1;
        }
        previous = slot;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        slot = retained;
    }
    void clearSlot() {
        igObject *previous = slot;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        slot = 0;
    }
};
extern "C" {
igObject *FUN_00187e10(int);
int FUN_0023b140(ObjectSlotOwner *, int);
igSmartPointer<igObject> FUN_0023b270(ObjectSlotOwner *owner, int value) {
    igSmartPointer<igObject> object(FUN_00187e10(0), AdoptReference());
    owner->setSlot(object);
    FUN_0023b140(owner, value);
    owner->clearSlot();
    return object;
}
}
