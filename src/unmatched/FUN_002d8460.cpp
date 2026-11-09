#include "dw4/igSmartPointer.h"

struct R : public igObject { };
extern "C" {
R *FUN_002d7c50();
}

extern "C" int FUN_002d8460(void) {
    igSmartPointer<R> h(FUN_002d7c50(), kRetainReference);
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}
