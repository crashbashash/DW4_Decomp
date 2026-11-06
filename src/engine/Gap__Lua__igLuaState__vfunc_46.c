/* Destructor (no delete flag) of the 4-byte, vtable-only object that FUN_00280a70 builds. Undoes
 * the constructor's two vtable writes in reverse: the derived image, then the base image (the same
 * one vfunc_54 leaves behind). */
#include "dw4/reflected.h"
/* Derived and base vtable images; the array form keeps the address load absolute. */
extern int g_derivedVtable_0052d710[4];
extern int g_baseVtable_0052d730[4];
igObject *Gap__Lua__igLuaState__vfunc_46(igObject *self) {
    if (self != 0) {
        self->_vtable = (int)&g_derivedVtable_0052d710[0];
        if (self != 0) {
            self->_vtable = (int)&g_baseVtable_0052d730[0];
        }
    }
    return self;
}
