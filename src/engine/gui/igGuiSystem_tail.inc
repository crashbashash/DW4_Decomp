/* The renderer is still flat: resetFields counts its scene and model references by hand. */
static inline void setReference(int &field, ::igObject *value)
{
    igObject::ref(value);
    ::igObject *old = (::igObject *)field;
    igObject::release(old);
    field = (int)value;
}

namespace Gap {
namespace Gui {

void igGuiSystem::resetFields(int persistent)
{
    igEventReceiver::resetFields(persistent);
    /* The observers are created by their flat C constructors, each adopted by the smart pointer (released, then
       its word set) as the kit's `observer = igXObserver::_instantiateFromPool(pool)` compiles. */
    igSmartPointer<igView> observer(0);
    int pool = (int)getMemoryPool();
    observer.release();
    observer.p = (igView *)igWindowSizeObserver_Create(pool);
    observer->setModel(_model);
    _viewList->append(observer);
    igSmartPointer<igView> mousePos((igView *)igMousePosObserver_Create((int)getMemoryPool()));
    ((::igMousePosObserver *)mousePos.get())->_guiSystem = (int)this;
    mousePos->setModel(_model);
    _viewList->append(mousePos);
    pool = (int)getMemoryPool();
    observer.release();
    observer.p = (igView *)igActiveComponentsObserver_Create(pool);
    observer->setModel(_model);
    _viewList->append(observer);
    _root->appendChild(_mouseCursorTransform);
    /* Byte-only: each value is read before the renderer is. */
    ::igObject *value = (::igObject *)_root.p;
    ::igGuiSystemRenderer *renderer = (::igGuiSystemRenderer *)_renderer.p;
    setReference(renderer->_root, value);
    value = (::igObject *)_model.p;
    renderer = (::igGuiSystemRenderer *)_renderer.p;
    setReference(renderer->_model, value);
}

void igGuiSystem::showCursor(bool visible)
{
    _mouseCursorVisible = visible;
    if (visible) {
        igGeometryElement *element = _mouseCursor->getGeometryElement();
        element->_color[0] = 1.0f;
        element->_color[1] = 1.0f;
        element->_color[2] = 1.0f;
        element->_color[3] = 1.0f;
        element->updateColor();
        return;
    }
    _mouseCursor->getGeometryElement()->setColor(g_vec4Zero);
}

void igGuiSystem::setMouseCursor(igMouseCursor *cursor)
{
    _mouseCursor = cursor;
    if (_mouseCursorTransform->getChildCount() > 0)
        _mouseCursorTransform->removeChild(0);
    if (cursor)
        _mouseCursorTransform->appendChild(cursor->getGeometryElement()->getGeometry());
    showCursor(_mouseCursorVisible);
    igNotifyEvent event(igGuiSystemModel::k_mousePosition);
    _model->notifyAllViews(event);
}

void igGuiSystem::updateMouseCursorPosition(igVec3f position)
{
    igMouseCursor *cursor = _mouseCursor;
    if (cursor) {
        float offsetX = cursor->_offset[0];
        float offsetY = cursor->_offset[1];
        float offsetZ = 0.0f;
        igMatrix44f matrix;
        position.vec[0] = position.vec[0] - offsetX;
        position.vec[1] = position.vec[1] - offsetY;
        position.vec[2] = position.vec[2] - offsetZ;
        igMatrix44f_SetTranslation(matrix.m, position.vec);
        _mouseCursorTransform->setMatrix(&matrix);
    }
}

void igGuiSystemModel::setFocusedComponent(igGuiComponent *component)
{
    _focusedComponent = component;
    igNotifyEvent event(k_focusedComponent);
    notifyAllViews(event);
}

void igGuiSystem::setRootComponent(igGuiComponent *component)
{
    if (_model->_rootComponent)
        _model->_rootComponent->setGuiSystem(0);
    _model->_rootComponent = component;
    igNotifyEvent event(igGuiSystemModel::k_rootComponent);
    _model->notifyAllViews(event);
    if (_root->getChildCount() > 1)
        _root->removeChild(0);
    if (component)
        _root->insertChild(0, (Sg::igNode *)component->getNode());
    if (component)
        component->setGuiSystem(this);
}

igGuiComponent *igGuiSystem::getNextComponent(igGuiComponent *component, IG_DIRECTION direction)
{
    igGuiComponent *next;
    if (component != 0) {
        while (1) {
            igGuiComponent *parent = component->getParent();
            if (parent == 0)
                return 0;
            next = parent->getNextChild(component, direction);
            component = parent;
            if (next != 0)
                break;
        }
    } else {
        next = _model->_rootComponent;
    }
    while (next != 0) {
        component = next;
        next = next->getNextChild(0, direction);
    }
    return component;
}

void igGuiSystem::move(IG_DIRECTION direction)
{
    igGuiComponent *component = _model->_focusedComponent;
    int keepsFocus = 0;
    if (component != 0)
        keepsFocus = ((Item_456eb0 *)component->getController())->test() & 0xFF;
    if (keepsFocus == 0) {
        do {
            component = getNextComponent(component, direction);
            if (component == _model->_focusedComponent || component == 0)
                break;
        } while ((component->isEnabled() != 0) ^ 1);
    }
    _model->setFocusedComponent(component);
}
}
}

