namespace Gap {
namespace Attrs {

igSmartPointer<igAttr> igGenericAttrDefaultManager::createDefaultAttr(igMetaObject *meta, int unitID) const
{
    igMetaObject_IsOfType(meta, igAttr::getClassMeta());
    return igMetaObject_CreateInstanceDefaultRef(meta);
}

void igGeometryAttr::synchronizeDefault(igVisualContext *vc)
{

}

bool igGeometryAttr::intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, ISET_SIDES whichFaces)
{
    int primIndex = -1;
    int polyIndex = -1;
    return intersectRay(ray, intersectPoint, norm, primIndex, polyIndex, whichFaces, false);
}

void igGeometryAttr::reset()
{
    if (_vertexArray != 0) {
        _vertexArray->reset();
    }
    if (_indexArray != 0) {
        _indexArray->reset();
    }
}
}
}

/* Empty override (a bare return) in vtable slot 35 of Gap::Core::igPsx2IndexArray, next to slot
 * 36, which is also empty. */
void FUN_0013d020(void) {
}

