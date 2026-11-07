#include "dw4/ipa/ipa_FUN_0015f430.h"
struct S { char p0[8]; int count; char p12[4]; int **items; };
int *FUN_0015f4a0(struct S *s, int a1, int a2) {
    int *found = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        int *item = s->items[i];
        if (FUN_0015f430(item, a1, a2, 0) != 0) { found = item; break; }
    }
    return found;
}
