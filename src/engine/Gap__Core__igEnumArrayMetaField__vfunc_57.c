/* 0x002dc870
 * Name of one enum value of this array field: fetches the field's igMetaEnum
 * through its _getMetaEnumFunction callback (+52) and looks `*value` up in it
 * with igMetaEnum_GetNameByValue (config/SLUS-20836/names/ObjectModel.tsv).  `result` is
 * passed straight through as that call's output string slot (the first
 * argument), with the receiver in the second register. */
#include "dw4/reflected.h"
int igMetaEnum_GetNameByValue();

void Gap__Core__igEnumArrayMetaField__vfunc_57(int result, igEnumArrayMetaField *self, int *value) {
    igMetaEnum_GetNameByValue(result, ((int (*)())self->_getMetaEnumFunction)(), *value);
}
