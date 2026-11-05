#include "dw4/reflected.h"
#include "dw4/typecast.h"
extern int DAT_00560f80[4];
int FUN_0022d1f0(igMetaField *arg0, int arg1, igMetaField *arg2, int arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    char *temp_v1;
    char *temp_a0;

    arg0 = (igMetaField *)dw4_cast_or_null((char *)arg0, DAT_00560f80);
    arg2 = (igMetaField *)dw4_cast_or_null((char *)arg2, DAT_00560f80);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + arg0->_offset);
        temp_v1 = (char *)(arg3 + arg2->_offset);
        *(long long *)(temp_v1 + 0) = *(long long *)(temp_a0 + 0);
        *(long long *)(temp_v1 + 8) = *(long long *)(temp_a0 + 8);
        *(long long *)(temp_v1 + 16) = *(long long *)(temp_a0 + 16);
        return 1;
    }
    return 0;
}
