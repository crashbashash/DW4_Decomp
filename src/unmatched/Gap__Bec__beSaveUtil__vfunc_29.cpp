#include "dw4/reflected.h"
extern "C" {
extern char DAT_00510738[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beSaveUtil__vfunc_29(beSaveUtil *, int, char *);
}
void Gap__Bec__beSaveUtil__vfunc_29(beSaveUtil * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_00510738);
}
