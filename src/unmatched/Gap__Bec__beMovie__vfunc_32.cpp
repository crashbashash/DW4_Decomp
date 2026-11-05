#include "dw4/reflected.h"
typedef struct RefObj { char p0[4]; int f4; } RefObj;
extern "C" {
void *FUN_00236f80(int, int);
int igObject_Destroy(RefObj *);
extern int DAT_00587870[4];
void Gap__Bec__beMovie__vfunc_32(beMovie *arg0);
}
void Gap__Bec__beMovie__vfunc_32(beMovie *arg0) {
    RefObj *temp_a0;
    RefObj *temp_v0;

    temp_v0 = (RefObj *)(FUN_00236f80(arg0->_insight, DAT_00587870[0]));
    if (temp_v0 != 0) {
        temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
    }
    temp_a0 = (RefObj *)(arg0->_movie);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_movie = (int)(temp_v0);
}
