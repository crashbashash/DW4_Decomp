/* 0x0017d8f0
 * Address of element `element` (8 bytes each) in the sub-array numbered
 * `index`: _vdata points at a table of base pointers whose first entry for
 * sub-array 0 sits at word 11 (0xB), so the base is read from word
 * `index + 11` and offset by `element * 8`. */
#include "dw4/reflected.h"
int Gap__Core__igPsx2VertexArray1_1__vfunc_52(igPsx2VertexArray1_1 *self, int index, int element) {
    return *(int *)(self->_vdata + ((index + 0xB) * 4)) + (element * 8);
}
