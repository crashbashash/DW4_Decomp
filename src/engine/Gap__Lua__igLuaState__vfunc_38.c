/* Deleting destructor of the 0x50-byte object built by FUN_00280810 (see vfunc_30). Sets only the
 * base vtable 0x0052d6f0, then calls FUN_00100610 when the signed low 16 bits of the delete flag
 * are positive; vfunc_30 calls the bare-return FUN_002809e0 at the same point. FUN_00100610 never
 * returns (asm/FUN_00100610.s ends in an endless loop). */
#include "dw4/reflected.h"
int FUN_00100610();
/* Base-class vtable image; the array form keeps the address load absolute. */
extern int g_baseVtable_0052d6f0[4];
igObject *Gap__Lua__igLuaState__vfunc_38(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_baseVtable_0052d6f0[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_00100610();
        }
    }
    return self;
}
