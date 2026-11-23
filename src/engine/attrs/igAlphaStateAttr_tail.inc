namespace Gap {
namespace Attrs {

void igAlphaStateAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setAlphaTestState(_enabled);
}

void igAlphaStateAttr::synchronizeDefault(igVisualContext *vc)
{
    setState(vc->getAlphaTestState());
}

void igAlphaStateAttr::setState(bool enabled)
{
    _enabled = enabled;
}
}
}

void FUN_0013b800(void)
{
}

namespace Gap {
namespace Attrs {

void igAttr::setUnitID(short id)
{
    _cachedUnitID = id;
}

void igAttr::userPostLoad()
{
    igObject::userPostLoad();
    _cachedUnitID = 0;
    _cachedAttrIndex = (short)getMeta()->_id;
}

void igAttr::resetFields(int flag)
{
    igObject::resetFields(flag);
    _cachedAttrIndex = (short)getMeta()->_id;
}

void igAttr::registerClass(igMetaObject *meta)
{
    if (igMetaObject_IsOfType(meta, getClassTypeSafe()) && !meta->_abstractState) {
        short index = _gNextAttrIndex;

        _gNextAttrIndex = index + 1;
        meta->_id = index;
    }
}
}
}

