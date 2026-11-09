#include "dw4/reflected.h"
extern "C" {
void beMessenger_SelectGroup(int, const char *);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, const char *);
extern char DAT_00519b00[];                 /* "DISPOFF" */
extern char DAT_00519b08[];                 /* "SWITCH" */
extern char DAT_00519c28[];                 /* "TEXTCTL" */
extern char DAT_00519db0[];                 /* "STWINFONT11" */
extern char DAT_00519d98[];                 /* "font100" */
extern char DAT_00519dc0[];
extern char DAT_00519dc8[];
extern char DAT_00519dd0[];
extern char DAT_00519dd8[];
extern char DAT_0051a018[];                 /* "font200" */
extern char DAT_0051a020[];
extern char DAT_0051a028[];
extern char DAT_0051a030[];
extern char DAT_0051a038[];
void Gap__Bec__beNDMWStatusSubSlot__vfunc_22(beNDMWStatusSubSlot *self);
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_22(beNDMWStatusSubSlot *self) {
    int i;
    for (i = 0; i < 5; i++) {
        const char *off = DAT_00519b00;
        const char *upper;
        const char *lower;
        switch (i) {
        default: upper = DAT_00519d98; lower = DAT_0051a018; break;
        case 1: upper = DAT_00519dc0; lower = DAT_0051a020; break;
        case 2: upper = DAT_00519dc8; lower = DAT_0051a028; break;
        case 3: upper = DAT_00519dd0; lower = DAT_0051a030; break;
        case 4: upper = DAT_00519dd8; lower = DAT_0051a038; break;
        }
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        beMessenger_AppendString(self->_messenger, DAT_00519db0);
        beMessenger_AppendString(self->_messenger, upper);
        beMessenger_AppendString(self->_messenger, off);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        beMessenger_AppendString(self->_messenger, DAT_00519db0);
        beMessenger_AppendString(self->_messenger, lower);
        beMessenger_AppendString(self->_messenger, off);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
    }
}
