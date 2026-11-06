/* Deleting destructor. Sets the vtable to the image at 0x0052dd30, then calls FUN_00100610 when
 * the signed low 16 bits of the delete flag are positive (same flag test as the Lua vfunc_38 /
 * vfunc_54). FUN_00100610 never returns (asm/FUN_00100610.s ends in an endless loop). */
#include "dw4/reflected.h"
int FUN_00100610();
/* Vtable image; the array form keeps the address load absolute. */
extern int g_vtable[4];
igObject *Gap__Core__igPsx2CallStackTracer__vfunc_34(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_vtable[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_00100610();
        }
    }
    return self;
}
