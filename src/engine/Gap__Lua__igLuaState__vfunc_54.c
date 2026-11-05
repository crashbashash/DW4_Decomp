/* 0x00280ad0 — Gap::Lua::igLuaState::vfunc_54: deleting destructor of the 4-byte,
 * vtable-only object that FUN_00280a70 builds.  Resets the vtable to the base-class
 * image 0x0052d730 (the constructor writes 0x0052d730, then 0x0052d710), then calls
 * FUN_00100610 when the signed low 16 bits of the delete flag are positive (same flag
 * test as vfunc_30 / vfunc_38).  FUN_00100610 never returns (asm/FUN_00100610.s ends in
 * an endless loop), so retail has no working release here. */
#include "dw4/reflected.h"
int FUN_00100610();
/* Base-class vtable image; the array form keeps the address load absolute. */
extern int g_baseVtable_0052d730[4];
igObject *Gap__Lua__igLuaState__vfunc_54(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_baseVtable_0052d730[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_00100610();
        }
    }
    return self;
}
