#include "dw4/reflected.h"

struct GuiModelView {
    char pad0[160];
    unsigned char enabled;
};

extern "C" {
void FUN_00456eb0(igGuiSystem *system, int direction);
void FUN_004570a0(igGuiSystem *system);
bool Gap__Gui__igGuiSystem__vfunc_27(igGuiSystem *system, int device, int key, int pressed);
}

bool Gap__Gui__igGuiSystem__vfunc_27(igGuiSystem *system, int device, int key, int pressed) {
    bool handled;

    if (!((GuiModelView *)system->_model)->enabled) {
        return false;
    }
    handled = false;
    switch (key) {
    case 4:
        if (pressed) {
            FUN_00456eb0(system, 2);
        }
        handled = true;
        break;
    case 6:
        if (pressed) {
            FUN_00456eb0(system, 3);
        }
        handled = true;
        break;
    case 7:
        if (pressed) {
            FUN_00456eb0(system, 0);
        }
        handled = true;
        break;
    case 5:
        if (pressed) {
            FUN_00456eb0(system, 1);
        }
        handled = true;
        break;
    case 8:
        if (pressed) {
            FUN_00456eb0(system, 5);
        }
        handled = true;
        break;
    case 9:
        if (pressed) {
            FUN_00456eb0(system, 4);
        }
        handled = true;
        break;
    case 13:
        if (pressed) {
            FUN_004570a0(system);
        }
        handled = true;
        break;
    }
    return handled;
}
