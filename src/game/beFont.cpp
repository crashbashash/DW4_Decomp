/* src/game/beFont.cpp — the beFont methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
void Gap__Core__igObject__vfunc_23(void);
void Gap__Bec__beFont__vfunc_23(void);
int beMessenger_RegisterReceiver(int, int, int *, int, int);
extern int TEXTCTL[4];
void Gap__Bec__beFont__vfunc_29(beFont *, int);
}

/* 0x003819a0 - slot 23: tail call to the base-class slot 23
 * (igObject::vfunc_23).  The receiver stays in the argument register, which is
 * why the declaration here takes no parameters. */
void Gap__Bec__beFont__vfunc_23(void)
{
    Gap__Core__igObject__vfunc_23();
}

/* 0x00381b40 - slot 29: register `receiver` with the font's messenger under
 * the "TEXTCTL" group string (0x0050e728, data/strings.json), with a null
 * text argument and -1 as the last argument. */
void Gap__Bec__beFont__vfunc_29(beFont *self, int receiver)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, &TEXTCTL[0], 0, -1);
}
