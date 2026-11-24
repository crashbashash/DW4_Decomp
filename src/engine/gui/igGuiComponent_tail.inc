namespace Gap {
namespace Gui {

void igGuiComponent::resetFields(int persistent)
{
    igObject::resetFields(persistent);
    _node->_component = (int)this;
}

void igGuiComponent::unlink()
{
    if (_linked) {
        if (_aspect) {
            ((igView *)_aspect.p)->setModel(0);
            _aspect->_node = 0;
        }
        ((igView *)_controller.p)->setModel(0);
        _model->setComponent(0);
        _linked = false;
    }
}

void igGuiComponent::userDestruct()
{
    igObject::userDestruct();
    if (_linked)
        unlink();
}

/* Byte-only: the node test is an inline returning from inside its `if`. Written as a conditional expression
   in getFromPath, the compiler inverts the isOfType branch and the depth test's delay slot no longer takes
   the index's first value (one instruction longer). */
static inline igGuiComponentNode *asComponentNode(igObject *object)
{
    if (object != 0 && object->isOfType(g_igGuiComponentNode_metaObject))
        return (igGuiComponentNode *)object;
    return 0;
}

igGuiComponent *igGuiComponent::getFromPath(igGraphPath *gp)
{
    int depth = gp->getDepth();
    if (depth <= 0)
        return 0;
    for (int i = depth - 1; i >= 0; i--) {
        igGuiComponentNode *node = asComponentNode(gp->_path->get(i));
        if (node != 0)
            return (igGuiComponent *)node->_component;
    }
    return 0;
}

igGuiComponent *igGuiComponent::getNextChild(igGuiComponent *child, IG_DIRECTION direction)
{
    return (igGuiComponent *)((igGuiComponentControllerView *)_controller.p)->vfunc_23(child, (void *)direction);
}

/* Retail's callers test the result unmasked: an int, not the kit's igBool. */
int igGuiComponent::isEnabled()
{
    return _model->_enabled;
}

/* The three setters pass the model's unsigned char flag on: retail's callers do not normalise it. */
void igGuiComponent::setHasFocus(unsigned char hasFocus)
{
    _model->setHasFocus(hasFocus);
}

void igGuiComponent::setMouseOver(unsigned char mouseOver)
{
    _model->setMouseOver(mouseOver);
}

void igGuiComponent::setPushed(unsigned char pushed)
{
    _model->setPushed(pushed);
}

/* Retail's callers mask the result: the model's unsigned char flag. */
unsigned char igGuiComponent::isPushed()
{
    return _model->_pushed;
}
}
}

