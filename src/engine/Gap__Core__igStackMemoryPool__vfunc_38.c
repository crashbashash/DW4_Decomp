/* 0x00327730: igStackMemoryPool slot 38, returns the reflected _alignment (+112, unsigned short; lhu in retail). */
#include "dw4/reflected.h"
unsigned short Gap__Core__igStackMemoryPool__vfunc_38(igStackMemoryPool *self) {
    return self->_alignment;
}
