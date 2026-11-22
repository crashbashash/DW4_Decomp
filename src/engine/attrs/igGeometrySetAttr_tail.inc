namespace Gap {
namespace Attrs {

bool igGeometrySetAttr::createRenderList(igVisualContext *vc)
{
    bool ok;
    int handle;
    igGeometryAttr **p;
    igGeometryAttr **end;
    handle = igPsx2VisualContext_CreateRenderList((igPsx2VisualContext *)vc);
    if (handle < 0) {
        _renderListState = 0;
        return false;
    }
    igPsx2VisualContext_BeginRenderListDraw((igPsx2VisualContext *)vc, handle);
    ok = true;
    p = (igGeometryAttr **)_geometryAttrList->_data;
    end = p + _geometryAttrList->getCount();
    for (; p < end; p++) {
        if ((*p)->isOfType((igMetaObject *)igGeometryAttr::getClassMeta()) == 0) {
            ok = false;
            break;
        }
        (*p)->apply(vc);
    }
    if ((igPsx2VisualContext_EndRenderListDraw((igPsx2VisualContext *)vc) & 0xFF) && ok) {
        setVisualContext(vc);
        _renderListHandle = handle;
        if (_renderListState == 2) {
            igGeometryAttr **q = (igGeometryAttr **)_geometryAttrList->_data;
            igGeometryAttr **qe = q + _geometryAttrList->getCount();
            for (; q < qe; q++) {
                (*q)->_vertexArray->releaseDefaults();
            }
        }
    } else {
        igPsx2VisualContext_DeleteRenderList((igPsx2VisualContext *)vc, handle);
        _renderListState = 0;
    }
    return ok;
}

void igGeometrySetAttr::setVisualContext(igVisualContext *vc)
{
    _vc = vc;
}

void igGeometrySetAttr::apply(igVisualContext *vc)
{
    int built = 0;
    if (_renderListState != 0) {
        if (_renderListHandle == -1) {
            built = createRenderList(vc);
        }
        if (_renderListHandle >= 0 && _drawState != 0) {
            built = igPsx2VisualContext_ExecuteRenderList((igPsx2VisualContext *)vc, _renderListHandle);
        }
    }
    if (built == 0 && _drawState != 0) {
        igGeometryAttr **p = (igGeometryAttr **)_geometryAttrList->_data;
        igGeometryAttr **e = p + _geometryAttrList->getCount();
        for (; p < e; p++) {
            (*p)->apply(vc);
        }
    }
}

void igGeometrySetAttr::setup(igVisualContext *vc)
{
    if (_renderListState != 0) {
        if (_renderListHandle == -1) {
            createRenderList(vc);
        }
    }
}

void igGeometrySetAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

void igGeometrySetAttr::reset()
{
    if (_geometryAttrList != 0) {
        int i;
        for (i = 0; i < _geometryAttrList->getCount(); i++) {
            _geometryAttrList->get(i)->reset();
        }
    }
    int handle = _renderListHandle;
    if (handle != -1) {
        ((igVisualContextDispatchView *)(igVisualContext *)_vc)->deleteRenderList(handle);
    }
    _renderListHandle = -1;
    _vc = 0;
}

/* Empty leaf in igGeometrySetAttr vtable slot 26: a do-nothing base-class hook. The receiver and
 * arguments are not used. */
void igGeometrySetAttr::synchronizeDefault(igVisualContext *vc)
{

}
}
}

