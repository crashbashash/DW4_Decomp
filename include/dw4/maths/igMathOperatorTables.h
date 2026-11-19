#ifndef DW4_IGMATHOPERATORTABLES_H
#define DW4_IGMATHOPERATORTABLES_H

#include "dw4/core/igSmartPointer.h"

struct igObject;

extern "C" {
/* Releases the held object; deletes the holder too when `deleteFlag` is positive. */
igSmartPointer<igObject> *FUN_0018f980(igSmartPointer<igObject> *self, short deleteFlag);
}

#endif
