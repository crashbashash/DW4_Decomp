#include "dw4/reflected.h"
extern "C" {
void Gap__Core__igObject__vfunc_23(void);
void Gap__Bec__beFont__vfunc_23(void);
int beMessenger_RegisterReceiver(int, int, int *, int, int);
extern int TEXTCTL[4];
void Gap__Bec__beFont__vfunc_29(beFont *, int);
}

/* Tail call to the base-class slot 23 (igObject::vfunc_23). The receiver stays in the argument
 * register, which is why the declaration takes no parameters. */
void Gap__Bec__beFont__vfunc_23(void)
{
    Gap__Core__igObject__vfunc_23();
}

/* Registers `receiver` with the font's messenger under the "TEXTCTL" group string, with a null
 * text argument and -1 as the last argument. */
void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, &TEXTCTL[0], 0, -1);
}
