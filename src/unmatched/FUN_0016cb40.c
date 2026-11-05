/* 0x0016cb40 - FUN_0016cb40. Per-entry fix-up loop with a status switch; first call also passes the receiver; alternate compiler. Verified byte-identical by tools/verify.py. */
#include "dw4/reflected.h"
int FUN_00177010();
int FUN_001e96d0();
int FUN_001ee730();
int FUN_001ee750();
struct L { char p[8]; int n; char q[4]; int *a; };
struct T { char p[16]; struct L ***tab; };
int FUN_0016cb40(igPsx2VisualContext *arg0, int arg1) {
    struct L *temp_s4;
    int temp_v0;
    int var_s2;
    int var_s1;
    int temp_v0_2;

    temp_s4 = *((struct T *)arg0->_pDLists)->tab[arg1];
    if (temp_s4->n > 0) {
        temp_v0 = FUN_00177010(arg0, 0, 0, temp_s4->a[0], arg1);
        if ((temp_v0 == 1) || (temp_v0 == 3)) {
            return 0;
        }
        var_s2 = 0;
        if (temp_v0 == 2) {
            var_s2 = FUN_001ee730(temp_s4->a[0]);
        }
        for (var_s1 = 0; var_s1 < temp_s4->n; var_s1 += 1) {
            temp_v0_2 = FUN_001ee730(temp_s4->a[var_s1]);
            if ((temp_v0 == 2) && (var_s2 != temp_v0_2)) {
                FUN_001e96d0(temp_v0_2, temp_v0_2);
            }
            FUN_001ee750(temp_s4->a[var_s1]);
        }
    }
    return 1;
}

