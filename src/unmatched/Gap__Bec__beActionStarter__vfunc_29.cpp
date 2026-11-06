#include "dw4/reflected.h"
extern "C" {
extern char DAT_0050e110[];
void beMessenger_RegisterReceiver(int, int, char *, int, int);
void Gap__Bec__beActionStarter__vfunc_29(beActionStarter *, int, char *, int, int);
}
void Gap__Bec__beActionStarter__vfunc_29(beActionStarter * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_0050e110, 0, -1);
}
