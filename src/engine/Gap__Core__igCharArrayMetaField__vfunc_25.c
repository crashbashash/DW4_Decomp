/* IgCharArrayMetaField virtual getter 25. Returns the array's storage size in bytes as 16 bits:
 * `_num` elements of one byte each, so it is `_num` itself (compare
 * igEnumArrayMetaField::vfunc_25, which scales by 4). */
#include "dw4/reflected.h"
unsigned short Gap__Core__igCharArrayMetaField__vfunc_25(igCharArrayMetaField *self) {
    return self->_num;
}
