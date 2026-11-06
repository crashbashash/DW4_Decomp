/* In C++ mode the compiler keeps the framed call in this one-call wrapper; C mode would tail-call
 * it. */
#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
extern int LOGO[4];
void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *, int);
}

/* Registers the logo controller with its messenger as the receiver named by the "LOGO" string.
 * Same one-call wrapper as beNDMWTitle2 and beFont slot 29. */
void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOGO[0]);
}
