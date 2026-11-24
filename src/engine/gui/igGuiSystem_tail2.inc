namespace Gap {
namespace Gui {

bool igGuiSystem::keyEvent(Display::igKey::KEY_VALUES key, bool status)
{
    if (!_model->_active)
        return false;
    bool handled = false;
    switch (key) {
    case Display::igKey::UP_ARROW:
        if (status)
            move(IG_DIRECTION_UP);
        handled = true;
        break;
    case Display::igKey::DOWN_ARROW:
        if (status)
            move(IG_DIRECTION_DOWN);
        handled = true;
        break;
    case Display::igKey::LEFT_ARROW:
        if (status)
            move(IG_DIRECTION_LEFT);
        handled = true;
        break;
    case Display::igKey::RIGHT_ARROW:
        if (status)
            move(IG_DIRECTION_RIGHT);
        handled = true;
        break;
    case Display::igKey::TAB:
        if (status)
            move(IG_DIRECTION_NEXT);
        handled = true;
        break;
    case Display::igKey::RETURN:
    case Display::igKey::SPACE:
        if (status)
            pressFocusedComponent();
        handled = true;
        break;
    default:
        break;
    }
    return handled;
}

void igGuiSystem::pressFocusedComponent()
{
    igGuiComponent *component = _model->_focusedComponent;
    if (component) {
        unsigned char pushed = component->isPushed() & 0xFF;
        component->setPushed(!pushed);
        component->setPushed(pushed);
    }
}

bool igGuiSystem::mouseMotionEvent(float x, float y)
{
    igGuiSystemModel *model = _model;
    if (!model->_active)
        return false;
    model->_mousePosition[0] = x;
    model->_mousePosition[1] = y;
    igNotifyEvent event(igGuiSystemModel::k_mousePosition);
    _model->notifyAllViews(event);
    return _model->_pushedComponent != 0;
}

bool igGuiSystem::windowResizeEvent(int width, int height)
{
    igGuiSystemModel *model = _model;
    model->_windowSize[0] = (float)width;
    model->_windowSize[1] = (float)height;
    igNotifyEvent event(igGuiSystemModel::k_windowSize);
    _model->notifyAllViews(event);
    return false;
}

bool igGuiSystem::windowCloseEvent()
{
    _model->_windowCloseRequested = true;
    igNotifyEvent event(igGuiSystemModel::k_windowCloseRequested);
    _model->notifyAllViews(event);
    return true;
}

bool igGuiSystem::mouseButtonEvent(Display::igMouse::MOUSE_BUTTON button, bool status)
{
    igGuiSystemModel *model = _model;
    if (!model->_active)
        return false;
    if (button != Display::igMouse::LEFT_BUTTON)
        return false;
    model->_mousePressed = status;
    igNotifyEvent event(igGuiSystemModel::k_mousePressed);
    _model->notifyAllViews(event);
    return _model->_componentUnderMouse != 0;
}

bool igGuiSystem::controllerButtonEvent(int controllerNum, Display::igController::BUTTONS button, bool status)
{
    if (!_model->_active)
        return false;
    bool handled = false;
    switch (button) {
    case Display::igController::LEFT_PAD_UP_BUTTON:
        if (status)
            move(IG_DIRECTION_UP);
        handled = true;
        break;
    case Display::igController::LEFT_PAD_DOWN_BUTTON:
        if (status)
            move(IG_DIRECTION_DOWN);
        handled = true;
        break;
    case Display::igController::LEFT_PAD_LEFT_BUTTON:
        if (status)
            move(IG_DIRECTION_LEFT);
        handled = true;
        break;
    case Display::igController::LEFT_PAD_RIGHT_BUTTON:
        if (status)
            move(IG_DIRECTION_RIGHT);
        handled = true;
        break;
    case Display::igController::LOWER_LEFT_TRIGGER:
        if (status)
            move(IG_DIRECTION_PREV);
        handled = true;
        break;
    case Display::igController::LOWER_RIGHT_TRIGGER:
        if (status)
            move(IG_DIRECTION_NEXT);
        handled = true;
        break;
    case Display::igController::RIGHT_PAD_RIGHT_BUTTON:
        if (status)
            pressFocusedComponent();
        handled = true;
        break;
    }
    return handled;
}

bool igGuiSystem::controllerMotionEvent(int controllerNum, unsigned short joystick, float x, float y)
{
    return false;
}

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

