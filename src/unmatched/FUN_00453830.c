#include "dw4/reflected.h"
int List_BinarySearch();
void FUN_00453370(void);
struct K { short key; char pad[38]; };
void FUN_00453830(beFontImage *arg0, short arg1) {
    struct K k;
    k.key = arg1;
    List_BinarySearch(arg0->_charMetricsList, &k, FUN_00453370, 0x28);
}
