#include "dw4/reflected.h"
int FUN_001e8a90(int, int, float, float, float, float, float, float);
extern int DAT_0048a560[4];
extern int DAT_005609e0[4];
void FUN_00175380(igPsx2VisualContext *arg0, float fparg0) {
    int temp_a1;

    if (arg0->_fogFar == fparg0) {
        DAT_005609e0[0] += 1;
    }
    arg0->_fogFar = fparg0;
    temp_a1 = arg0->_fogMode;
    FUN_001e8a90(DAT_0048a560[temp_a1], temp_a1, arg0->_fogNear, arg0->_fogFar, arg0->_fogDensity, 1.0f, 0.0f, 0.0f);
}
