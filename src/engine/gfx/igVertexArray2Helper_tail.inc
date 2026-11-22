/* A vertex data holds its list as a counted reference (the kit's igVertexData::setData, igVertexData's own
 * code is flat here). */
template <class List> static inline void setVertexDataList(igVertexData *vertexData, const igSmartPointer<List> &list)
{
    igObject *data = (igObject *)list.p;
    igObject::ref(data);
    igObject *previous = (igObject *)vertexData->_data;
    igObject::release(previous);
    vertexData->_data = (int)data;
}

/* The new vertex data arrives with its reference already counted (an adopted reference): the old one is
 * released and the new one stored without a second count. */
static inline void recreateVertexData(igSmartPointer<igVertexData> &vertexData, igMemoryPoolView *pool)
{
    vertexData.release();
    vertexData.p = (igVertexData *)igVertexData_Create((int)pool);
}

namespace Gap {
namespace Gfx {

unsigned int igVertexArray2Helper::configure(const igVertexFormat &vertexFormat, unsigned int vertexCount)
{
    if (_vertexArray != 0) {
        return 0;
    }
    igSmartPointer<igVertexArray2> array(igVertexArray2::_instantiateFromPool(getMemoryPool()));
    _vertexArray = array;
    igSmartPointer<igVertexData> vertexData;
    if (vertexFormat.hasPositions()) {
        igSmartPointer<igVec3fList> list(igVec3fList_Create(getMemoryPool()));
        ((Gap::Core::igTDataList<igVec3f> *)list.p)->setCount(vertexCount);
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_POSITION;
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.hasNormals()) {
        igSmartPointer<igVec3fList> list(igVec3fList_Create(getMemoryPool()));
        ((Gap::Core::igTDataList<igVec3f> *)list.p)->setCount(vertexCount);
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_NORMAL;
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.hasVertexColors()) {
        igSmartPointer<igVec4ucList> list(igVec4ucList_Create(getMemoryPool()));
        ((Gap::Core::igTDataList<igVec4uc> *)list.p)->setCount(vertexCount);
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_COLOR;
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.getTextureCoordCount() != 0) {
        for (unsigned int index = 0; index < vertexFormat.getTextureCoordCount(); index++) {
            igSmartPointer<igVec2fList> list(igVec2fList_Create(getMemoryPool()));
            ((Gap::Core::igTDataList<igVec2f> *)list.p)->setCount(vertexCount);
            recreateVertexData(vertexData, getMemoryPool());
            setVertexDataList(vertexData, list);
            vertexData->_componentType = IG_VERTEX_COMPONENT_TEXCOORD;
            vertexData->_componentIndex = index;
            array->getObjectList()->append((igObject *)vertexData.p);
        }
    }
    if (vertexFormat.getBlendWeightCount() != 0) {
        igSmartPointer<igFloatList> list(igFloatList::_instantiateFromPool(getMemoryPool()));
        list->setCount(vertexCount * vertexFormat.getBlendWeightCount());
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_WEIGHT;
        vertexData->_componentSize = vertexFormat.getBlendWeightCount();
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.getBlendIndexCount() != 0) {
        igSmartPointer<igUnsignedCharList> list(igUnsignedCharList::_instantiateFromPool(getMemoryPool()));
        list->setCount(vertexCount * vertexFormat.getBlendIndexCount());
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_INDEX;
        vertexData->_componentSize = vertexFormat.getBlendIndexCount();
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    unsigned char coordCount = vertexFormat.getPointSpriteCoordCount();
    if (coordCount != 0) {
        /* matching construct: retail zero-extends the count a second time into the register it compares */
        unsigned int sizeCount = coordCount & 0xFF;
        recreateVertexData(vertexData, getMemoryPool());
        vertexData->_componentType = IG_VERTEX_COMPONENT_SIZE;
        if (sizeCount == 1) {
            igSmartPointer<igFloatList> list(igFloatList::_instantiateFromPool(getMemoryPool()));
            list->setCount(vertexCount);
            setVertexDataList(vertexData, list);
        } else if (sizeCount == 2) {
            igSmartPointer<igVec2fList> list(igVec2fList_Create(getMemoryPool()));
            ((Gap::Core::igTDataList<igVec2f> *)list.p)->setCount(vertexCount);
            setVertexDataList(vertexData, list);
        }
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.hasBinormals()) {
        igSmartPointer<igVec3fList> list(igVec3fList_Create(getMemoryPool()));
        ((Gap::Core::igTDataList<igVec3f> *)list.p)->setCount(vertexCount);
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_BINORMAL;
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    if (vertexFormat.hasTangents()) {
        igSmartPointer<igVec3fList> list(igVec3fList_Create(getMemoryPool()));
        ((Gap::Core::igTDataList<igVec3f> *)list.p)->setCount(vertexCount);
        recreateVertexData(vertexData, getMemoryPool());
        setVertexDataList(vertexData, list);
        vertexData->_componentType = IG_VERTEX_COMPONENT_TANGENT;
        array->getObjectList()->append((igObject *)vertexData.p);
    }
    return vertexCount;
}

void igVertexArray2Helper::setUsageFlags(unsigned int flags)
{
    igVertexStream::IG_VERTEX_ACCESS_MODE accessMode = igVertexStream::IG_VERTEX_ACCESS_READ_WRITE;
    if (flags & IG_GFX_USAGE_WRITE_ONLY) {
        accessMode = igVertexStream::IG_VERTEX_ACCESS_WRITE;
    }
    igVertexArray2 *vertexArray = _vertexArray;
    if (vertexArray == 0) {
        return;
    }
    if (vertexArray->_vertexStream != 0) {
        vertexArray->_vertexStream->setAccessMode(accessMode);
        return;
    }
    igSmartPointer<igVertexStream> stream(igVertexStream::_instantiateFromPool(getMemoryPool()));
    if (stream != 0) {
        stream->setAccessMode(accessMode);
        _vertexArray->setVertexStream(stream);
    }
}

unsigned int igVertexArray2Helper::getUsageFlags() const
{
    unsigned int usageFlags = 0;
    igVertexArray2 *vertexArray = _vertexArray;
    if (vertexArray != 0) {
        igVertexStream *stream = vertexArray->_vertexStream;
        if (stream != 0 && stream->getAccessMode() == igVertexStream::IG_VERTEX_ACCESS_WRITE) {
            usageFlags = IG_GFX_USAGE_WRITE_ONLY;
        }
    }
    return usageFlags;
}

void igVertexArray2Helper::setPosition(unsigned int idx, const igVec3f &pos)
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_POSITION, 0)->_data, &g_igVec3fList_metaObject);
    list->set(idx, pos);
}

void igVertexArray2Helper::getPosition(unsigned int idx, igVec3f &pos) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_POSITION, 0)->_data, &g_igVec3fList_metaObject);
    pos = list->get(idx);
}

const igVec3f * igVertexArray2Helper::getPosition(unsigned int idx) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_POSITION, 0)->_data, &g_igVec3fList_metaObject);
    return &list->get(idx);
}

void igVertexArray2Helper::setNormal(unsigned int idx, const igVec3f &normal)
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_NORMAL, 0)->_data, &g_igVec3fList_metaObject);
    list->set(idx, normal);
}

void igVertexArray2Helper::getNormal(unsigned int idx, igVec3f &normal) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_NORMAL, 0)->_data, &g_igVec3fList_metaObject);
    normal = list->get(idx);
}

const igVec3f * igVertexArray2Helper::getNormal(unsigned int idx) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_NORMAL, 0)->_data, &g_igVec3fList_metaObject);
    return &list->get(idx);
}

void igVertexArray2Helper::setBinormal(unsigned int idx, const igVec3f &binormal)
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_BINORMAL, 0)->_data, &g_igVec3fList_metaObject);
    list->set(idx, binormal);
}

void igVertexArray2Helper::getBinormal(unsigned int idx, igVec3f &binormal) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_BINORMAL, 0)->_data, &g_igVec3fList_metaObject);
    binormal = list->get(idx);
}

const igVec3f * igVertexArray2Helper::getBinormal(unsigned int idx) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_BINORMAL, 0)->_data, &g_igVec3fList_metaObject);
    return &list->get(idx);
}

void igVertexArray2Helper::setTangent(unsigned int idx, const igVec3f &tangent)
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TANGENT, 0)->_data, &g_igVec3fList_metaObject);
    list->set(idx, tangent);
}


void igVertexArray2Helper::getTangent(unsigned int idx, igVec3f &tangent) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TANGENT, 0)->_data, &g_igVec3fList_metaObject);
    tangent = list->get(idx);
}

const igVec3f * igVertexArray2Helper::getTangent(unsigned int idx) const
{
    Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TANGENT, 0)->_data, &g_igVec3fList_metaObject);
    return &list->get(idx);
}

void igVertexArray2Helper::setColor(unsigned int idx, unsigned int abgr)
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_COLOR, 0);
    if (Gap::Core::igUnsignedIntList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        ((Gap::Core::igUnsignedIntList *)vertexData->_data)->set(idx, abgr);
    } else if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        ((Gap::Core::igTDataList<igVec4uc> *)vertexData->_data)->set(idx, *(igVec4uc *)&abgr);
    }
}

void igVertexArray2Helper::setColor(unsigned int idx, const igVec4f &rgba)
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_COLOR, 0);
    if (Gap::Core::igUnsignedIntList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igUnsignedIntList *list = (Gap::Core::igUnsignedIntList *)vertexData->_data;
        list->set(idx, igVec4f_PackColor(rgba.vec, IG_MATH_COLORSPACE_FORMAT_RGBA));
    } else if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec4uc> *list = (Gap::Core::igTDataList<igVec4uc> *)vertexData->_data;
        unsigned int abgr = igVec4f_PackColor(rgba.vec, IG_MATH_COLORSPACE_FORMAT_RGBA);
        list->set(idx, *(igVec4uc *)&abgr);
    }
}

unsigned int igVertexArray2Helper::getColor(unsigned int idx) const
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_COLOR, 0);
    if (Gap::Core::igUnsignedIntList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        return ((Gap::Core::igUnsignedIntList *)vertexData->_data)->get(idx);
    }
    if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        return *(unsigned int *)&((Gap::Core::igTDataList<igVec4uc> *)vertexData->_data)->get(idx);
    }
    return 0;
}

void igVertexArray2Helper::getColor(unsigned int idx, igVec4f &rgba) const
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_COLOR, 0);
    if (Gap::Core::igUnsignedIntList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Color4f_Unpack(&rgba, IG_MATH_COLORSPACE_FORMAT_RGBA, ((Gap::Core::igUnsignedIntList *)vertexData->_data)->get(idx));
        return;
    }
    if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Color4f_Unpack(&rgba, IG_MATH_COLORSPACE_FORMAT_RGBA, *(unsigned int *)&((Gap::Core::igTDataList<igVec4uc> *)vertexData->_data)->get(idx));
    }
}

void igVertexArray2Helper::setWeight(unsigned int which, unsigned int idx, float weight)
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_WEIGHT, 0);
    if (Gap::Core::igFloatList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igFloatList *list = (Gap::Core::igFloatList *)vertexData->_data;
        list->set(which + idx * vertexData->_componentSize, weight);
    }
    else if (g_igVec2fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)vertexData->_data;
        igVec2f vec = list->get(idx);
        vec[which] = weight;
        list->set(idx, vec);
    }
    else if (g_igVec3fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec3f> *list = (Gap::Core::igTDataList<igVec3f> *)vertexData->_data;
        igVec3f vec = list->get(idx);
        vec[which] = weight;
        list->set(idx, vec);
    }
    else if (g_igVec4fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec4f> *list = (Gap::Core::igTDataList<igVec4f> *)vertexData->_data;
        igVec4f vec = list->get(idx);
        vec[which] = weight;
        list->set(idx, vec);
    }
}

float igVertexArray2Helper::getWeight(unsigned int which, unsigned int idx) const
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_WEIGHT, 0);
    if (Gap::Core::igFloatList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        return ((Gap::Core::igFloatList *)vertexData->_data)->get(which + idx * vertexData->_componentSize);
    }
    if (g_igVec2fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        igVec2f vec = ((Gap::Core::igTDataList<igVec2f> *)vertexData->_data)->get(idx);
        return vec[which];
    }
    if (g_igVec3fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        igVec3f vec = ((Gap::Core::igTDataList<igVec3f> *)vertexData->_data)->get(idx);
        return vec[which];
    }
    if (g_igVec4fList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        igVec4f vec = ((Gap::Core::igTDataList<igVec4f> *)vertexData->_data)->get(idx);
        return vec[which];
    }
    return 0.0f;
}

void igVertexArray2Helper::setBlendMatrixIndex(unsigned int which, unsigned int vertexIndex, unsigned char matrixIndex)
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_INDEX, 0);
    if (Gap::Core::igUnsignedCharList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igUnsignedCharList *list = (Gap::Core::igUnsignedCharList *)vertexData->_data;
        list->set(which + vertexIndex * vertexData->_componentSize, matrixIndex);
    } else if (g_igVec3ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec3uc> *list = (Gap::Core::igTDataList<igVec3uc> *)vertexData->_data;
        igVec3uc vec = list->get(vertexIndex);
        vec[which] = matrixIndex;
        list->set(vertexIndex, vec);
    } else if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        Gap::Core::igTDataList<igVec4uc> *list = (Gap::Core::igTDataList<igVec4uc> *)vertexData->_data;
        igVec4uc vec = list->get(vertexIndex);
        vec[which] = matrixIndex;
        list->set(vertexIndex, vec);
    }
}

unsigned char igVertexArray2Helper::getBlendMatrixIndex(unsigned int which, unsigned int idx) const
{
    igVertexData *vertexData = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_INDEX, 0);
    if (Gap::Core::igUnsignedCharList::getClassMeta() == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        return ((Gap::Core::igUnsignedCharList *)vertexData->_data)->get(which + idx * vertexData->_componentSize);
    }
    if (g_igVec3ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        igVec3uc vec = ((Gap::Core::igTDataList<igVec3uc> *)vertexData->_data)->get(idx);
        return vec[which];
    }
    if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)vertexData->_data)->getMeta()) {
        igVec4uc vec = ((Gap::Core::igTDataList<igVec4uc> *)vertexData->_data)->get(idx);
        return vec[which];
    }
    return 0;
}

void igVertexArray2Helper::setTextureCoord(unsigned int which, unsigned int idx, const igVec2f &coord)
{
    Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TEXCOORD, which)->_data, &g_igVec2fList_metaObject);
    list->set(idx, coord);
}

void igVertexArray2Helper::getTextureCoord(unsigned int which, unsigned int idx, igVec2f &coord) const
{
    Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TEXCOORD, which)->_data, &g_igVec2fList_metaObject);
    coord = list->get(idx);
}

const igVec2f * igVertexArray2Helper::getTextureCoord(unsigned int which, unsigned int idx) const
{
    Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TEXCOORD, which)->_data, &g_igVec2fList_metaObject);
    return &list->get(idx);
}

void igVertexArray2Helper::setPointSpriteSize(unsigned int idx, float size)
{
    Gap::Core::igObject *data = (Gap::Core::igObject *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_SIZE, 0)->_data;
    Gap::Core::igFloatList *list;
    if (data != 0 && data->isOfType(Gap::Core::igFloatList::getClassMeta()) != 0) {
        list = (Gap::Core::igFloatList *)data;
    } else {
        list = 0;
    }
    list->set(idx, size);
}

float igVertexArray2Helper::getPointSpriteSize(unsigned int idx) const
{
    Gap::Core::igObject *data = (Gap::Core::igObject *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_SIZE, 0)->_data;
    Gap::Core::igFloatList *list;
    if (data != 0 && data->isOfType(Gap::Core::igFloatList::getClassMeta()) != 0) {
        list = (Gap::Core::igFloatList *)data;
    } else {
        list = 0;
    }
    return list->get(idx);
}

void igVertexArray2Helper::setPointSpriteSize(unsigned int idx, igVec2f &size)
{
    Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_SIZE, 0)->_data, &g_igVec2fList_metaObject);
    list->set(idx, size);
}

void igVertexArray2Helper::getPointSpriteSize(unsigned int idx, igVec2f &size) const
{
    Gap::Core::igTDataList<igVec2f> *list = (Gap::Core::igTDataList<igVec2f> *)dw4_cast_or_null((char *)_vertexArray->findVertexData(IG_VERTEX_COMPONENT_SIZE, 0)->_data, &g_igVec2fList_metaObject);
    size = list->get(idx);
}

unsigned int igVertexArray2Helper::getWeightCount()
{
    return getWeightCount(_vertexArray->findVertexData(IG_VERTEX_COMPONENT_WEIGHT, 0));
}

unsigned int igVertexArray2Helper::getIndexCount()
{
    return getIndexCount(_vertexArray->findVertexData(IG_VERTEX_COMPONENT_INDEX, 0));
}

void igVertexArray2Helper::copyVertex(const unsigned int destIndex, const igVertexArray *sourceVertexArray, const unsigned int sourceIndex, const igVertexFormat &fieldMask)
{
    if (fieldMask.hasPositions()) {
        setPosition(destIndex, *sourceVertexArray->getPosition(sourceIndex));
    }
    if (fieldMask.hasNormals()) {
        setNormal(destIndex, *sourceVertexArray->getNormal(sourceIndex));
    }
    if (fieldMask.hasBinormals()) {
        setBinormal(destIndex, *sourceVertexArray->getBinormal(sourceIndex));
    }
    if (fieldMask.hasTangents()) {
        setTangent(destIndex, *sourceVertexArray->getTangent(sourceIndex));
    }
    if (fieldMask.hasVertexColors()) {
        setColor(destIndex, sourceVertexArray->getColor(sourceIndex));
    }
    /* matching construct: retail zero-extends each count a second time where it uses it (as in
     * igVertexArray2::configure) */
    unsigned int i;
    unsigned char count = fieldMask.getBlendWeightCount();
    if (count != 0) {
        for (i = 0; i < (count & 0xFF); i++) {
            setWeight(i, destIndex, sourceVertexArray->getWeight(i, sourceIndex));
        }
    }
    count = fieldMask.getBlendIndexCount();
    if (count != 0) {
        for (i = 0; i < (count & 0xFF); i++) {
            unsigned char matrixIndex = sourceVertexArray->getBlendMatrixIndex(i, sourceIndex);
            setBlendMatrixIndex(i, destIndex, matrixIndex);
        }
    }
    count = fieldMask.getPointSpriteCoordCount();
    if (count != 0) {
        if ((count & 0xFF) == 1) {
            setPointSpriteSize(destIndex, sourceVertexArray->getPointSpriteSize(sourceIndex));
        } else if ((count & 0xFF) == 2) {
            igVec2f size;
            sourceVertexArray->getPointSpriteSize(sourceIndex, size);
            setPointSpriteSize(destIndex, size);
        }
    }
    count = fieldMask.getTextureCoordCount();
    if (count != 0) {
        for (i = 0; i < (count & 0xFF); i++) {
            setTextureCoord(i, destIndex, *sourceVertexArray->getTextureCoord(i, sourceIndex));
        }
    }
}

unsigned int igVertexArray2Helper::reconfigure(const igVertexFormat &vertexFormat, unsigned int vertexCount, unsigned int usageFlags, igVisualContext *context)
{
    return 0;
}

void igVertexArray2Helper::getVertexFormat(igVertexFormat *vertexFormat)
{
    igVertexData *positions = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_POSITION, 0);
    igVertexData *normals = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_NORMAL, 0);
    igVertexData *colors = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_COLOR, 0);
    igVertexData *weights = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_WEIGHT, 0);
    igVertexData *indices = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_INDEX, 0);
    igVertexData *tangents = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_TANGENT, 0);
    igVertexData *binormals = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_BINORMAL, 0);
    igVertexData *sizes = _vertexArray->findVertexData(IG_VERTEX_COMPONENT_SIZE, 0);
    if (positions != 0) {
        vertexFormat->setHasPositions(true);
    }
    if (normals != 0) {
        vertexFormat->setHasNormals(true);
    }
    if (colors != 0) {
        vertexFormat->setHasVertexColors(true);
    }
    if (weights != 0) {
        vertexFormat->setBlendWeightCount(getWeightCount());
    }
    if (indices != 0) {
        vertexFormat->setBlendIndexCount(getIndexCount());
    }
    if (tangents != 0) {
        vertexFormat->setHasTangents(true);
    }
    if (binormals != 0) {
        vertexFormat->setHasBinormals(true);
    }
    if (sizes != 0) {
        Gap::Core::igObject *data = (Gap::Core::igObject *)sizes->_data;
        Gap::Core::igFloatList *list;
        if (data != 0 && data->isOfType(Gap::Core::igFloatList::getClassMeta()) != 0) {
            list = (Gap::Core::igFloatList *)data;
        } else {
            list = 0;
        }
        vertexFormat->setPointSpriteCoordCount(list != 0 ? 1 : 2);
    }
    unsigned int textureCoordCount = 0;
    while (_vertexArray->findVertexData(IG_VERTEX_COMPONENT_TEXCOORD, textureCoordCount) != 0) {
        textureCoordCount++;
    }
    vertexFormat->setTextureCoordCount(textureCoordCount);
}

unsigned int igVertexArray2Helper::getWeightCount(igVertexData *weightVertexData)
{
    if (Gap::Core::igFloatList::getClassMeta() == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta() ||
        Gap::Core::igCharList::getClassMeta() == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta() ||
        Gap::Core::igUnsignedCharList::getClassMeta() == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta() ||
        Gap::Core::igShortList::getClassMeta() == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta() ||
        Gap::Core::igUnsignedShortList::getClassMeta() == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta()) {
        return weightVertexData->_componentSize;
    }
    if (g_igVec2fList_metaObject == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta()) {
        return 2;
    }
    if (g_igVec3fList_metaObject == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta()) {
        return 3;
    }
    if (g_igVec4fList_metaObject == ((Gap::Core::igObject *)weightVertexData->_data)->getMeta()) {
        return 4;
    }
    return 0;
}

unsigned int igVertexArray2Helper::getIndexCount(const igVertexData *indexVertexData)
{
    if (Gap::Core::igUnsignedCharList::getClassMeta() == ((Gap::Core::igObject *)indexVertexData->_data)->getMeta()) {
        return indexVertexData->_componentSize;
    }
    if (g_igVec3ucList_metaObject == ((Gap::Core::igObject *)indexVertexData->_data)->getMeta()) {
        return 3;
    }
    if (g_igVec4ucList_metaObject == ((Gap::Core::igObject *)indexVertexData->_data)->getMeta()) {
        return 4;
    }
    return 0;
}

void igVertexArray2Helper::getMinValue(IG_VERTEX_COMPONENT_TYPE type, float &minNum, int index)
{
    igVertexData *vertexData = _vertexArray->findVertexData(type, index);
    Gap::Core::igFloatList *scalars;
    Gap::Core::igTDataList<igVec2f> *pairs;
    Gap::Core::igTDataList<igVec3f> *triples;
    Gap::Core::igTDataList<igVec4f> *quads;
    Gap::Core::igObject *list;
    int i;
    int count;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in the pair (case 4)
     * and quad blocks set the float register order */
    float x, y, z;

    minNum = 1e23f;
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(Gap::Core::igFloatList::getClassMeta()) != 0) {
        scalars = (Gap::Core::igFloatList *)list;
    } else {
        scalars = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec2fList_metaObject) != 0) {
        pairs = (Gap::Core::igTDataList<igVec2f> *)list;
    } else {
        pairs = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec3fList_metaObject) != 0) {
        triples = (Gap::Core::igTDataList<igVec3f> *)list;
    } else {
        triples = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec4fList_metaObject) != 0) {
        quads = (Gap::Core::igTDataList<igVec4f> *)list;
    } else {
        quads = 0;
    }
    switch (type) {
    case IG_VERTEX_COMPONENT_POSITION:
    case IG_VERTEX_COMPONENT_NORMAL:
    case IG_VERTEX_COMPONENT_BINORMAL:
    case IG_VERTEX_COMPONENT_TANGENT:
        if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec3f &vec = triples->get(i);
                if (x > vec[0]) x = vec[0];
                if (y > vec[1]) y = vec[1];
                if (z > vec[2]) z = vec[2];
            }
            minNum = (x < y) ? x : y;
            minNum = (minNum < z) ? minNum : z;
        }
        break;
    case IG_VERTEX_COMPONENT_TEXCOORD:
        if (pairs != 0) {
            float x = 1e23f, y = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec2f &vec = pairs->get(i);
                if (x > vec[0]) x = vec[0];
                if (y > vec[1]) y = vec[1];
            }
            minNum = (x < y) ? x : y;
        }
        break;
    case IG_VERTEX_COMPONENT_WEIGHT:
    case IG_VERTEX_COMPONENT_SIZE:
        if (scalars != 0) {
            float m = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                m = (m < scalars->get(i)) ? m : scalars->get(i);
            }
            minNum = m;
        } else if (pairs != 0) {
            x = 1e23f; y = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec2f &vec = pairs->get(i);
                if (x > vec[0]) x = vec[0];
                if (y > vec[1]) y = vec[1];
            }
            minNum = (x < y) ? x : y;
        } else if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec3f &vec = triples->get(i);
                if (x > vec[0]) x = vec[0];
                if (y > vec[1]) y = vec[1];
                if (z > vec[2]) z = vec[2];
            }
            minNum = (x < y) ? x : y;
            minNum = (minNum < z) ? minNum : z;
        } else if (quads != 0) {
            float x = 1e23f, y = 1e23f, z = 1e23f, w = 1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec4f &vec = quads->get(i);
                if (x > vec[0]) x = vec[0];
                if (y > vec[1]) y = vec[1];
                if (z > vec[2]) z = vec[2];
                if (w > vec[3]) w = vec[3];
            }
            minNum = (x < y) ? x : y;
            minNum = (minNum < z) ? minNum : z;
            minNum = (minNum < w) ? minNum : w;
        }
        break;
    }
}

void igVertexArray2Helper::getMaxValue(IG_VERTEX_COMPONENT_TYPE type, float &maxNum, int index)
{
    igVertexData *vertexData = _vertexArray->findVertexData(type, index);
    Gap::Core::igFloatList *scalars;
    Gap::Core::igTDataList<igVec2f> *pairs;
    Gap::Core::igTDataList<igVec3f> *triples;
    Gap::Core::igTDataList<igVec4f> *quads;
    Gap::Core::igObject *list;
    int i;
    int count;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in the pair (case 4)
     * and quad blocks set the float register order */
    float x, y, z;

    maxNum = -1e23f;
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(Gap::Core::igFloatList::getClassMeta()) != 0) {
        scalars = (Gap::Core::igFloatList *)list;
    } else {
        scalars = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec2fList_metaObject) != 0) {
        pairs = (Gap::Core::igTDataList<igVec2f> *)list;
    } else {
        pairs = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec3fList_metaObject) != 0) {
        triples = (Gap::Core::igTDataList<igVec3f> *)list;
    } else {
        triples = 0;
    }
    list = (Gap::Core::igObject *)vertexData->_data;
    if (list != 0 && list->isOfType(g_igVec4fList_metaObject) != 0) {
        quads = (Gap::Core::igTDataList<igVec4f> *)list;
    } else {
        quads = 0;
    }
    switch (type) {
    case IG_VERTEX_COMPONENT_POSITION:
    case IG_VERTEX_COMPONENT_NORMAL:
    case IG_VERTEX_COMPONENT_BINORMAL:
    case IG_VERTEX_COMPONENT_TANGENT:
        if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec3f &vec = triples->get(i);
                if (x < vec[0]) x = vec[0];
                if (y < vec[1]) y = vec[1];
                if (z < vec[2]) z = vec[2];
            }
            maxNum = (x > y) ? x : y;
            maxNum = (maxNum > z) ? maxNum : z;
        }
        break;
    case IG_VERTEX_COMPONENT_TEXCOORD:
        if (pairs != 0) {
            float x = -1e23f, y = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec2f &vec = pairs->get(i);
                if (x < vec[0]) x = vec[0];
                if (y < vec[1]) y = vec[1];
            }
            maxNum = (x > y) ? x : y;
        }
        break;
    case IG_VERTEX_COMPONENT_WEIGHT:
    case IG_VERTEX_COMPONENT_SIZE:
        if (scalars != 0) {
            float m = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                m = (m > scalars->get(i)) ? m : scalars->get(i);
            }
            maxNum = m;
        } else if (pairs != 0) {
            x = -1e23f; y = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec2f &vec = pairs->get(i);
                if (x < vec[0]) x = vec[0];
                if (y < vec[1]) y = vec[1];
            }
            maxNum = (x > y) ? x : y;
        } else if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec3f &vec = triples->get(i);
                if (x < vec[0]) x = vec[0];
                if (y < vec[1]) y = vec[1];
                if (z < vec[2]) z = vec[2];
            }
            maxNum = (x > y) ? x : y;
            maxNum = (maxNum > z) ? maxNum : z;
        } else if (quads != 0) {
            float x = -1e23f, y = -1e23f, z = -1e23f, w = -1e23f;
            count = ((Gap::Core::igDataList *)vertexData->_data)->_count;
            for (i = 0; i < count; i++) {
                igVec4f &vec = quads->get(i);
                if (x < vec[0]) x = vec[0];
                if (y < vec[1]) y = vec[1];
                if (z < vec[2]) z = vec[2];
                if (w < vec[3]) w = vec[3];
            }
            maxNum = (x > y) ? x : y;
            maxNum = (maxNum > z) ? maxNum : z;
            maxNum = (maxNum > w) ? maxNum : w;
        }
        break;
    }
}
}
}

/* `value` as a fixed-point word with `fractionBits` fraction bits: the integer part shifted up, joined by the
 * mantissa bits below the binary point, read through the float's bit fields (the union is read back through the
 * stack; the exponent bias is subtracted after the join, not inside the condition). */
int igVertexArray2Helper_FloatToFixedPoint(float value, unsigned int fractionBits) {
    union { float f; unsigned u; struct { unsigned mantissa:23; } bits; } x;
    int exponent, power;
    unsigned int pointShift, fraction, fixedFraction, mantissa;
    int integerPart;
    x.f = value;
    exponent = (x.u >> 23) & 0xFF;
    mantissa = x.bits.mantissa;
    if (mantissa != 0 || exponent != 0) {
        mantissa |= 0x800000;
    }
    power = exponent - 0x7F;
    pointShift = 23;
    if (power != 0) {
        pointShift -= power;
    } else {
        pointShift += power;
    }
    fraction = mantissa & ((1 << pointShift) - 1);
    integerPart = (int)x.f;
    if (fractionBits < pointShift) {
        fixedFraction = fraction >> (pointShift - fractionBits);
    } else {
        fixedFraction = fraction << (fractionBits - pointShift);
    }
    return fixedFraction | (integerPart << fractionBits);
}

/* The integer part of a fixed-point word with `fractionBits` fraction bits, as a float. */
float igVertexArray2Helper_FixedPointToFloat(int value, int fractionBits) {
    return (float)(value >> fractionBits);
}

ObjectRefWord *FUN_00164870(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igShortList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igCharList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int *FUN_001649f0(void) {
    static int listMetaObjects[5] = { (int)g_igVec3fList_metaObject, (int)Gap::Core::igCharList::getClassMeta(), (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)Gap::Core::igShortList::getClassMeta(), (int)Gap::Core::igUnsignedShortList::getClassMeta() };
    return listMetaObjects;
}

int *FUN_00164a60(void) {
    static int listMetaObjects[2] = { (int)Gap::Core::igUnsignedIntList::getClassMeta(), (int)g_igVec4ucList_metaObject };
    return listMetaObjects;
}

int *FUN_00164aa0(void) {
    static int listMetaObjects[5] = { (int)g_igVec3fList_metaObject, (int)Gap::Core::igCharList::getClassMeta(), (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)Gap::Core::igShortList::getClassMeta(), (int)Gap::Core::igUnsignedShortList::getClassMeta() };
    return listMetaObjects;
}

int *FUN_00164b10(void) {
    static int listMetaObjects[5] = { (int)g_igVec2fList_metaObject, (int)Gap::Core::igCharList::getClassMeta(), (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)Gap::Core::igShortList::getClassMeta(), (int)Gap::Core::igUnsignedShortList::getClassMeta() };
    return listMetaObjects;
}

int *FUN_00164b80(void) {
    static int listMetaObjects[8] = { (int)Gap::Core::igFloatList::getClassMeta(), (int)g_igVec2fList_metaObject, (int)g_igVec3fList_metaObject, (int)g_igVec4fList_metaObject, (int)Gap::Core::igCharList::getClassMeta(), (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)Gap::Core::igShortList::getClassMeta(), (int)Gap::Core::igUnsignedShortList::getClassMeta() };
    return listMetaObjects;
}

int *FUN_00164c20(void) {
    static int listMetaObjects[3] = { (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)g_igVec3ucList_metaObject, (int)g_igVec4ucList_metaObject };
    return listMetaObjects;
}

int *FUN_00164c70(void) {
    static int listMetaObjects[1] = { (int)g_igVec3fList_metaObject };
    return listMetaObjects;
}

int *FUN_00164ca0(void) {
    static int listMetaObjects[1] = { (int)g_igVec3fList_metaObject };
    return listMetaObjects;
}

int *FUN_00164cd0(void) {
    static int listMetaObjects[6] = { (int)Gap::Core::igFloatList::getClassMeta(), (int)g_igVec2fList_metaObject, (int)Gap::Core::igCharList::getClassMeta(), (int)Gap::Core::igUnsignedCharList::getClassMeta(), (int)Gap::Core::igShortList::getClassMeta(), (int)Gap::Core::igUnsignedShortList::getClassMeta() };
    return listMetaObjects;
}

int *FUN_00164d50(void) {
    return &DAT_00560750[0];
}

namespace Gap {
namespace Gfx {

bool igVertexArray2::isVertexDataSupported(const igVertexData *vertexData) const
{
    int *metas = 0;
    int meta;
    switch (vertexData->_componentType) {
    case 1: metas = FUN_001649f0(); break;
    case 2: metas = FUN_00164a60(); break;
    case 3: metas = FUN_00164aa0(); break;
    case 4: metas = FUN_00164b10(); break;
    case 5: metas = FUN_00164b80(); break;
    case 6: metas = FUN_00164c20(); break;
    case 7: metas = FUN_00164c70(); break;
    case 8: metas = FUN_00164ca0(); break;
    case 9: metas = FUN_00164cd0(); break;
    case 10: metas = FUN_00164d50(); break;
    }
    while ((meta = *metas) != 0) {
        if (meta == (int)((igDataList *)vertexData->_data)->getMeta()) {
            return true;
        }
        metas++;
    }
    return false;
}
}
}

