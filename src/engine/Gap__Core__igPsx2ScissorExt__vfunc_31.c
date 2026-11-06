/* Reports whether scissoring is enabled: returns _scissorEnable (+24). Field name and offset come
 * from the reflected igPsx2ScissorExt record (include/dw4/reflected.h). */
#include "dw4/reflected.h"
unsigned char Gap__Core__igPsx2ScissorExt__vfunc_31(igPsx2ScissorExt *self) {
    return self->_scissorEnable;
}
