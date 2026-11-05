extern volatile float GPR_00554930;
extern volatile float GPR_00554950;
extern volatile float GPR_00554954;
extern volatile float GPR_00554958;
int Matrix44_Copy();
struct S { char p0[12]; unsigned char f12; unsigned char f13; };
#include "dw4/ipa/ipa_InRange_001419f0.h"
void FUN_001419f0(struct S *arg0, float *m, void *arg2) {
    if (InRange(m[0], &GPR_00554950, &GPR_00554954) &&
        InRange(m[1], &GPR_00554958, &GPR_00554930) &&
        InRange(m[2], &GPR_00554958, &GPR_00554930) &&
        InRange(m[3], &GPR_00554958, &GPR_00554930) &&
        InRange(m[4], &GPR_00554958, &GPR_00554930) &&
        InRange(m[5], &GPR_00554950, &GPR_00554954) &&
        InRange(m[6], &GPR_00554958, &GPR_00554930) &&
        InRange(m[7], &GPR_00554958, &GPR_00554930) &&
        InRange(m[8], &GPR_00554958, &GPR_00554930) &&
        InRange(m[9], &GPR_00554958, &GPR_00554930) &&
        InRange(m[10], &GPR_00554950, &GPR_00554954) &&
        InRange(m[11], &GPR_00554958, &GPR_00554930) &&
        InRange(m[12], &GPR_00554958, &GPR_00554930) &&
        InRange(m[13], &GPR_00554958, &GPR_00554930) &&
        InRange(m[14], &GPR_00554958, &GPR_00554930) &&
        InRange(m[15], &GPR_00554950, &GPR_00554954)) {
        arg0->f12 = 1;
    } else {
        arg0->f12 = 0;
    }
    Matrix44_Copy((char *)arg0 + 28, m);
    Matrix44_Copy((char *)arg0 + 92, arg2);
    arg0->f13 = 1;
}
