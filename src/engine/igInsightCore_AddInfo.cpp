/* Offers `info` to each manager in the core's manager list, in order, stopping at the first one
 * whose virtual slot 27 (vtable +0x6c) returns non-zero; then appends `info` to the core's
 * `_infoList` with a retained reference, whether or not a manager took it. `_managerList` is a
 * holder whose +8 field is the igObjectList of managers. */
#include "dw4/reflected.h"
extern "C" {
int ObjectList_AppendRetained(...);
void igInsightCore_AddInfo(igInsightCore *self, int info);
}
/* Dummy class with 25 virtual slots before vX, so that vX is the manager's
 * vtable slot 27 (matching construct: gives the retail `lw t9,108(t9)` call). */
class DW4VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
void igInsightCore_AddInfo(igInsightCore *self, int info) {
    unsigned int index;
    igObjectList *managers;

    for (index = 0; managers = (igObjectList *)((igSerialScheduler *)self->_managerList)->_managerList, index < (unsigned int)managers->_count; index++) {
        int byteOffset = index * 4;
        DW4VC *manager = (DW4VC *)*(int *)(managers->_data + byteOffset);
        if (manager->vX(info) != 0) {
            break;
        }
    }
    ObjectList_AppendRetained(self->_infoList, info);
}
