/* Struct member access under the alternate compiler (delay slot and padding nop); verified by tools/verify.py. */
#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(beUnicodeObj *);
int Memory_FreeBufferWithAllocator(int, int);
int igObject_GetAllocator();
void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *arg0);
}

void Gap__Bec__beUnicodeObj__vfunc_08(beUnicodeObj *arg0) {
    if (arg0->_buffer != 0) {
        Memory_FreeBufferWithAllocator(arg0->_buffer, igObject_GetAllocator());
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
