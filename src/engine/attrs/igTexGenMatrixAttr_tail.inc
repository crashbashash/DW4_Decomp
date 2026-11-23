namespace Gap {
namespace Attrs {

void igTexGenMatrixAttr::synchronizeCachedUnitID(igObject *obj)
{
    igTexGenMatrixAttr *attr = (igTexGenMatrixAttr *)obj;

    attr->setCachedUnitID(attr->_unitID);
}

void igTexGenMatrixAttr::setUnitID(short id)
{
    _unitID = id;
    igAttr::setUnitID(id);
}

void igTexGenMatrixAttr::userPostLoad()
{
    igVisualAttribute::userPostLoad();
    igAttr::setUnitID((short)_unitID);
}

void igTexGenMatrixAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->setMatrixPsx2(14, m.m);
}

void igTexGenMatrixAttr::synchronizeDefault(igVisualContext *vc)
{
    igMatrix44f matrix;

    ((igPsx2VisualContext *)vc)->getMatrixPsx2(14, matrix.m);
    igMatrix44f_Copy(m.m, matrix.m);
}
}
}

