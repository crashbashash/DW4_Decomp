namespace Gap {
namespace Gfx {

igVertexData *igVertexArray2::findVertexData(unsigned int type, unsigned int index) const
{
    igVertexData *result = 0;
    int i;
    int n = _objList->getCount();
    for (i = 0; i < n; i++) {
        igVertexData *data = (igVertexData *)dw4_cast_or_null((char *)_objList->get(i), (int *)&g_igVertexData_metaObject);
        if (type == data->_componentType && index == data->_componentIndex) {
            result = data;
            break;
        }
    }
    return result;
}

bool igVertexArray2::configure(IG_GFX_DRAW primitive, igIndexArray *indexArray, igPrimLengthArray *primLengthArray, igVisualContext *vc)
{
    igSmartPointer<igVertexArray> array(igVertexArray::_instantiateFromPool((igMemoryPoolView *)getMemoryPool()));
    if (array == 0) {
        return false;
    }
    igSmartPointer<igVertexArray2HelperAccess> helper(igVertexArray2Helper_Create((int)getMemoryPool()));
    if (helper == 0) {
        return false;
    }
    helper->setVertexArray((igVertexArray2View *)this);
    igVertexFormat format;
    helper->getFormat(&format);
    unsigned int count = getCount(0);
    array->configure(format, count, helper->getUsageFlags(), vc);
    unsigned int j;
    unsigned int i;
    if (format.hasPositions()) {
        for (i = 0; i < count; i++) {
            array->setPosition(i, *helper->getPosition(i));
        }
    }
    if (format.hasNormals()) {
        for (i = 0; i < count; i++) {
            array->setNormal(i, *helper->getNormal(i));
        }
    }
    if (format.hasVertexColors()) {
        for (i = 0; i < count; i++) {
            array->setColor(i, helper->getColor(i));
        }
    }
    if (format.getBlendWeightCount() != 0) {
        for (i = 0; i < count; i++) {
            unsigned int j;
            for (j = 0; j < format.getBlendWeightCount(); j++) {
                array->setWeight(j, i, helper->getWeight(j, i));
            }
        }
    }
    if (format.getBlendIndexCount() != 0) {
        for (i = 0; i < count; i++) {
            for (j = 0; j < format.getBlendIndexCount(); j++) {
                array->setBlendMatrixIndex(j, i, helper->getBlendIndex(j, i));
            }
        }
    }
    if (format.hasTangents()) {
        for (i = 0; i < count; i++) {
            array->setTangent(i, *helper->getTangent(i));
        }
    }
    if (format.hasBinormals()) {
        for (i = 0; i < count; i++) {
            array->setBinormal(i, *helper->getBinormal(i));
        }
    }
    unsigned char c = format.getPointSpriteCoordCount();
    /* matching construct: retail zero-extends the count a second time where it compares it */
    if (c) {
        if ((c & 0xFF) == 1) {
            for (i = 0; i < count; i++) {
                array->setPointSpriteSize(i, helper->getPointSize(i));
            }
        } else if ((c & 0xFF) == 2) {
            for (i = 0; i < count; i++) {
                igVec2f size;
                helper->getPointSize2(i, &size);
                array->setPointSpriteSize(i, size);
            }
        }
    }
    if (format.getTextureCoordCount() != 0) {
        for (i = 0; i < count; i++) {
            unsigned int j;
            for (j = 0; j < format.getTextureCoordCount(); j++) {
                array->setTextureCoord(j, i, *helper->getTextureCoord(j, i));
            }
        }
    }
    _internalBuffer = array;
    return true;
}

void igVertexArray2::buildVertexDataList(igSmartPointer<igVertexDataList> list)
{
    int i;
    ((igObjectList *)list.p)->setCount(0);
    for (i = 0; i < _objList->getCount(); i++) {
        igVertexData *data = (igVertexData *)dw4_cast_or_null((char *)_objList->get(i), (int *)&g_igVertexData_metaObject);
        if (data != 0 && isVertexDataSupported(data)) {
            ((igObjectList *)list.p)->append((igObject *)data);
        }
    }
}

/* matching construct: _data is a 4-byte reference field; the casts give the typed views (no layout effect) */
unsigned int igVertexArray2::getCount(unsigned int index) const
{
    igVertexData *data = findVertexData(1, index);
    if (data != 0) {
        igMetaObject *meta = (igMetaObject *)g_igVec3fList_metaObject;
        if (meta == ((igDataList *)data->_data)->getMeta()) {
            return ((igDataList *)data->_data)->getCount();
        }
        meta = (igMetaObject *)DAT_005610a8[0];
        if (meta == ((igDataList *)data->_data)->getMeta()) {
            return ((igDataList *)data->_data)->getCount();
        }
    }
    return 0;
}
}
}

