#include "dw4/reflected.h"
extern "C" {
extern char DAT_00510200[];
void beMessenger_RegisterReceiver(int, int, char *, int, int);
void Gap__Bec__beMovie__vfunc_29(beMovie *, int, char *, int, int);
}
void Gap__Bec__beMovie__vfunc_29(beMovie * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_00510200, 0, -1);
}
