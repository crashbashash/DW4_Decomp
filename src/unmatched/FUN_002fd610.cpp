#include "dw4/igSmartPointer.h"
struct Instance : public igObject { };
extern "C" {
Instance *igMetaObject_CreateInstanceDefault(int);
}
static inline void retain(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

extern "C" int FUN_002fd610(Instance **out, int meta) {
    igSmartPointer<Instance> created(igMetaObject_CreateInstanceDefault(meta), kRetainReference);
    release(created.p);
    *out = created.p;
    retain(*out);
    return 0;
}
