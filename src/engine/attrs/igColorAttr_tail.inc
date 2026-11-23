namespace Gap {
namespace Attrs {

void igColorAttr::initDefaults()
{
    igVisualAttribute::initDefaults();
    _colorPacked = igVec4f_PackColor(_color.vec, 1);
}

void igColorAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    _colorPacked = igVec4f_PackColor(_color.vec, 1);
}

void igColorAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetColorPacked((igPsx2VisualContext *)vc, _colorPacked);
}

void igColorAttr::synchronizeDefault(igVisualContext *vc)
{
    _colorPacked = vc->getColor();
}

void igColorAttr::colorChanged(igObject *obj)
{
    igColorAttr *attr = (igColorAttr *)obj;

    attr->_colorPacked = igVec4f_PackColor(attr->_color.vec, 1);
}
}
}

