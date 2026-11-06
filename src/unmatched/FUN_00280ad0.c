/* Deleting destructor of the 4-byte, vtable-only object that FUN_00280a70 builds. Resets the
 * vtable to the base-class image (the constructor writes the base image, then the derived one),
 * then calls FUN_00100610 when the signed low 16 bits of the delete flag are positive (same flag
 * test as FUN_00280890 / FUN_00280840). FUN_00100610 never returns, so retail has no working release here. */
#include "dw4/reflected.h"
int FUN_00100610();
/* Base-class vtable image; the array form keeps the address load absolute. */
extern int g_baseVtable_0052d730[4];
igObject *FUN_00280ad0(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_baseVtable_0052d730[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_00100610();
        }
    }
    return self;
}
