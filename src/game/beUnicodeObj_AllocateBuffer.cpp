#include "dw4/reflected.h"
extern "C" {
int memset(int, int, unsigned int);
int FUN_002ed2b0(unsigned int, int, int);
int Memory_FreeBufferWithAllocator(int, int);
unsigned int Memory_GetBufferSize(int);
int igObject_GetAllocator(void *);
void beUnicodeObj_AllocateBuffer(beUnicodeObj *arg0, int arg1);
}

void beUnicodeObj_AllocateBuffer(beUnicodeObj *arg0, int arg1) {
    unsigned int need;
    if (arg0->_buffer != 0) {
        need = (arg1 + 1) * 2;
        if (Memory_GetBufferSize(arg0->_buffer) < need) {
            Memory_FreeBufferWithAllocator(arg0->_buffer, igObject_GetAllocator(arg0));
            arg0->_buffer = FUN_002ed2b0(need, 0x10, igObject_GetAllocator(arg0));
        }
    } else {
        arg0->_buffer = FUN_002ed2b0((arg1 + 1) * 2, 0x10, igObject_GetAllocator(arg0));
    }
    memset(arg0->_buffer, 0, Memory_GetBufferSize(arg0->_buffer));
}
