/* IgLuaState slot 33, returns the object reference count (_refCount at +4, inherited from
 * igObject). */
#include "dw4/reflected.h"
int FUN_002809c0(igLuaState *self) {
    return self->_refCount;
}
