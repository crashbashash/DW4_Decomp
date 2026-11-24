namespace Gap {
namespace Gui {

bool igHotKeyEventReceiver::keyEvent(Display::igKey::KEY_VALUES key, bool status)
{
    if (!status)
        return false;
    int count = _hotKeyList->getCount();
    for (int i = 0; i < count; i++) {
        igHotKeyBinding *binding = _hotKeyList->get(i);
        if (binding->_key == key) {
            binding->_action->doIt();
            return true;
        }
    }
    return false;
}

bool igHotKeyEventReceiver::controllerButtonEvent(int controllerNum, Display::igController::BUTTONS button, bool status)
{
    if (!status)
        return false;
    int count = _hotKeyList->getCount();
    for (int i = 0; i < count; i++) {
        igHotKeyBinding *binding = _hotKeyList->get(i);
        if (binding->_button == button) {
            binding->_action->doIt();
            return true;
        }
    }
    return false;
}
}
}

