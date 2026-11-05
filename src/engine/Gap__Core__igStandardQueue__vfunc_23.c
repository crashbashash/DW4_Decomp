/* 0x00328670: allocate the queue's element storage, one 4-byte slot per entry of _capacity. */
#include "dw4/reflected.h"
int igObject_AllocateStorage();

void Gap__Core__igStandardQueue__vfunc_23(igStandardQueue *self) {
    self->_data = igObject_AllocateStorage(self, self->_capacity * 4);
}
