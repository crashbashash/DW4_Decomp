namespace Gap {
namespace Attrs {

void igProjectionMatrixAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setMatrix(IG_GFX_MATRIX_STACK_PROJECTION, _m);
}

void igProjectionMatrixAttr::synchronizeDefault(igVisualContext *vc)
{
    igMatrix44f m;

    vc->getMatrix(IG_GFX_MATRIX_STACK_PROJECTION, m);
    setMatrix(m);
}

void igProjectionMatrixAttr::setMatrix(const igMatrix44f &matrix)
{
    igMatrix44f_Copy(_m.m, matrix.m);
}
}
}

