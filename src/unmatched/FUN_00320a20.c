/* 0x00320a20 - FUN_00320a20. Byte-swaps an array of 40-byte records (ten words each) in place; the word swap helper is compiled first in the same unit so the loop counter and pointer stay in a1/a2 across the calls (interprocedural register use); verified with the helper as a duplicate. */
#include "dw4/ipa/ipa_FUN_00320960.h"
void FUN_00320a20(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320960(p + 12);
        FUN_00320960(p + 16);
        FUN_00320960(p + 20);
        FUN_00320960(p + 24);
        FUN_00320960(p + 28);
        FUN_00320960(p + 32);
        FUN_00320960(p + 36);
        p += 40;
    }
}
