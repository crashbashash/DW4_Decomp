/* IgLuaState slot 33, returns the object reference count (_refCount at +4, inherited from
 * igObject). */
#include "dw4/reflected.h"
int Gap__Lua__igLuaState__vfunc_33(igLuaState *self) {
    return self->_refCount;
}
