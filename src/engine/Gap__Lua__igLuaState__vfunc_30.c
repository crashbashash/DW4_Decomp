/* Deleting destructor of the 0x50-byte object built by FUN_00280810. Its constructor writes the
 * base vtable and then the derived one; this undoes that in reverse, then releases the storage
 * when the signed low 16 bits of the flag are positive (same flag test as vfunc_38). FUN_002809e0
 * is a bare return, so no release actually happens in retail. */
#include "dw4/reflected.h"
int FUN_002809e0();
/* Vtable images of the derived and base class; arrays keep the address load absolute. */
extern int g_derivedVtable_0052d6d0[4];
extern int g_baseVtable_0052d6f0[4];
igObject *Gap__Lua__igLuaState__vfunc_30(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_derivedVtable_0052d6d0[0];
        if (self != 0) {
            self->_vtable = (int)&g_baseVtable_0052d6f0[0];
        }
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_002809e0(self);
        }
    }
    return self;
}
