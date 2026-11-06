/* The swap helpers are compiled first in the same unit so the loop counter and pointer stay in
 * a1/a2 across the calls (interprocedural register use). */
#include "dw4/ipa/ipa_FUN_00320930.h"
#include "dw4/ipa/ipa_FUN_00320960.h"
void FUN_00320aa0(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320930(p + 14);
        p += 16;
    }
}
