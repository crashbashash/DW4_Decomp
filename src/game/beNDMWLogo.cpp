/* src/game/beNDMWLogo.cpp — C++-mode beNDMWLogo methods.
 *
 * MWCC's C++ front end preserves the framed call used by this one-call wrapper;
 * the C front end tail-calls it instead. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
extern int LOGO[4];
void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *, int);
}

/* slot 29: register the logo controller with its messenger as the receiver named by the "LOGO"
 * string at 0x0051db38. Same one-call wrapper as beNDMWTitle2 and beFont slot 29. */
void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOGO[0]);
}
