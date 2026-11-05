#include "dw4/reflected.h"
int List_BinarySearch();
void FUN_00453370(void);  /* code at 0x453370, passed by address (was DAT_453370; docs/engine/function-inventory.md) */
struct K { short key; char pad[38]; };
void FUN_00453830(beFontImage *arg0, short arg1) {
    struct K k;
    k.key = arg1;
    List_BinarySearch(arg0->_charMetricsList, &k, FUN_00453370, 0x28);
}
