bool igGuiSystem_OnKeyEvent(Ob *arg0, int arg1, int arg2) {
    if (arg0->f12->f160 == 0) {
        return false;
    }
    bool r = false;
    switch (arg1) {
    case 0x81:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 2);
        }
        r = true;
        break;
    case 0x83:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 3);
        }
        r = true;
        break;
    case 0x80:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 0);
        }
        r = true;
        break;
    case 0x82:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 1);
        }
        r = true;
        break;
    case 0x9:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 4);
        }
        r = true;
        break;
    case 0xD:
    case 0x20:
        if (arg2 != 0) {
            FUN_004570a0(arg0);
        }
        r = true;
        break;
    default:
        break;
    }
    return r;
}

void FUN_004570a0(void *arg0) {
    unsigned char temp_s1;
    int temp_s0;
    temp_s0 = *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 168);
    if (temp_s0 != 0) {
        temp_s1 = FUN_00455620((void *)temp_s0) & 0xFF;
        FUN_00455610((int *)temp_s0, !temp_s1);
        FUN_00455610((int *)temp_s0, temp_s1);
    }
}

int igGuiSystem_MouseMotionEvent(A_457100 *arg0, float fparg0, float fparg1) {
    B_457100 *temp_v1;

    temp_v1 = arg0->fc;
    if (temp_v1->fa0 == 0) {
        return 0;
    }
    temp_v1->f14 = fparg0;
    temp_v1->f18 = fparg1;
    igNotifyEvent s((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_mousePosition);
    ((Gap::Gui::igModel *)arg0->fc)->notifyAllViews(s);
    return arg0->fc->fb0 != 0;
}

int igGuiSystem_WindowResizeEvent(int *self, int x, int y) {
    float *f = (float *)self[3];
    f[3] = (float)x;
    f[4] = (float)y;
    igNotifyEvent p((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_windowSize);
    ((Gap::Gui::igModel *)((void *)self[3]))->notifyAllViews(p);
    return 0;
}

int igGuiSystem_WindowCloseEvent(igGuiSystem *arg0) {

    *(char *)((char *)(arg0->_model) + 180) = 1;
    igNotifyEvent buf((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_windowCloseRequested);
    ((Gap::Gui::igModel *)arg0->_model)->notifyAllViews(buf);
    return 1;
}

int igGuiSystem_MouseButtonEvent(struct P_457220 *arg0, int arg1, char arg2) {
    struct O_457220 *o;

    o = arg0->o;
    if (o->fa0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        return 0;
    }
    o->f1c = arg2;
    igNotifyEvent sp((Gap::Core::igMetaField *)Gap::Gui::igGuiSystemModel::k_mousePressed);
    ((Gap::Gui::igModel *)arg0->o)->notifyAllViews(sp);
    return arg0->o->fac != 0;
}

bool igGuiSystem_ControllerButtonEvent(igGuiSystem *system, int device, int key, int pressed) {
    bool handled;

    if (!((GuiModelView *)system->_model)->enabled) {
        return false;
    }
    handled = false;
    switch (key) {
    case 4:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 2);
        }
        handled = true;
        break;
    case 6:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 3);
        }
        handled = true;
        break;
    case 7:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 0);
        }
        handled = true;
        break;
    case 5:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 1);
        }
        handled = true;
        break;
    case 8:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 5);
        }
        handled = true;
        break;
    case 9:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 4);
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

int igGuiSystem_ControllerMotionEvent(void) {
    return 0;
}

namespace Gap {
namespace Gui {

void igHotKeyEventReceiver::appendHotKey(Display::igKey::KEY_VALUES key, igAction *action)
{
    appendHotKey(key, Display::igController::MAX_BUTTONS, action);
}

void igHotKeyEventReceiver::appendHotKey(Display::igController::BUTTONS button, igAction *action)
{
    appendHotKey(Display::igKey::UNKNOWN, button, action);
}

void igHotKeyEventReceiver::appendHotKey(Display::igKey::KEY_VALUES key, Display::igController::BUTTONS button, igAction *action)
{
    igSmartPointer<igHotKeyBinding> binding(igHotKeyBinding::_instantiateFromPool(getMemoryPool()));
    binding->_key = key;
    binding->_button = button;
    binding->_action = action;
    _hotKeyList->append(binding);
}

void igHotKeyEventReceiver::removeHotKey(Display::igController::BUTTONS button)
{
    for (int i = _hotKeyList->getCount() - 1; i >= 0; i--) {
        igHotKeyBinding *binding = _hotKeyList->get(i);
        if (binding->_button == button) {
            if (binding->_key == Display::igKey::UNKNOWN)
                _hotKeyList->remove(i);
            else
                binding->_button = Display::igController::MAX_BUTTONS;
        }
    }
}
}
}

