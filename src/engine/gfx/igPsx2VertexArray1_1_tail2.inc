namespace Gap {
namespace Gfx {

void igPsx2VertexArray1_1::releaseDefaults()
{
    if (_usageFlags & 4) {
        p2WaitDmaSequence(1, _lSequence);
    }
    if (_vdata != 0) {
        freeAbstractVertexArrayMemory();
        free(_vdata);
        _vdata = 0;
        _numVerts = 0;
    }
    freeBlendedVertexLists();
    igVertexArray1_1::releaseDefaults();
}

void igPsx2VertexArray1_1::reset()
{
}

unsigned int igPsx2VertexArray1_1::configure(const igVertexFormat &vertexFormat, unsigned int vertexCount, unsigned int usageFlags, igVisualContext *context)
{
    unsigned int total;

    if (_numVerts != 0) {
        return 0;
    }
    _numVerts = vertexCount;
    total = 0;
    _vertexFormat = vertexFormat;
    _vtype = 0;
    _usageFlags = usageFlags;
    _vdata = (void **)getMemoryPool()->Callocate(20, sizeof(void *));
    total += 20 * sizeof(void *);
    total += allocateAbstractVertexArrayMemory();
    if (vertexFormat.getBlendWeightCount() > 0) {
        allocateBlendedVertexLists();
    }
    return total;
}

/* The blended-vertex lists a skinned array keeps between frames: the DMA wait sequences, the blended positions
 * and, with normals, the blended normals. */
void igPsx2VertexArray1_1::allocateBlendedVertexLists()
{
    const igVertexFormat &vertexFormat = getVertexFormat();
    if (vertexFormat.getBlendWeightCount() > 0) {
        igMemoryPoolView *pool = getMemoryPool();
        _pWaitSeqList.release();
        _pWaitSeqList.p = (::igPsx2LongList *)igPsx2LongList_Create((int)pool);
        pool = getMemoryPool();
        _pBlendedVertsList.release();
        _pBlendedVertsList.p = (igPointerList *)igPointerList_Create((int)pool);
        if (vertexFormat.hasNormals()) {
            pool = getMemoryPool();
            _pBlendedNormsList.release();
            _pBlendedNormsList.p = (igPointerList *)igPointerList_Create((int)pool);
        }
    }
}

void igPsx2VertexArray1_1::freeBlendedVertexLists()
{
    int i;

    _pWaitSeqList.clear();
    i = 0;
    if (_pBlendedVertsList != 0) {
        for (; i < _pBlendedVertsList->getCount(); i++) {
            Memory_FreeBuffer(_pBlendedVertsList->get(i));
        }
    }
    i = 0;
    if (_pBlendedNormsList != 0) {
        for (; i < _pBlendedNormsList->getCount(); i++) {
            Memory_FreeBuffer(_pBlendedNormsList->get(i));
        }
    }
    _pBlendedVertsList.clear();
    _pBlendedNormsList.clear();
}

void igPsx2VertexArray1_1::setPosition(unsigned int idx, const igVec3f &position)
{
    ((igVec3f *)_vdata[0])[idx] = position;
}

void igPsx2VertexArray1_1::getPosition(unsigned int idx, igVec3f &position) const
{
    position = ((igVec3f *)_vdata[0])[idx];
}

const igVec3f *igPsx2VertexArray1_1::getPosition(unsigned int idx) const
{
    return (igVec3f *)_vdata[0] + idx;
}

void igPsx2VertexArray1_1::setNormal(unsigned int idx, const igVec3f &normal)
{
    ((igVec3f *)_vdata[1])[idx] = normal;
}

void igPsx2VertexArray1_1::getNormal(unsigned int idx, igVec3f &normal) const
{
    normal = ((igVec3f *)_vdata[1])[idx];
}

const igVec3f *igPsx2VertexArray1_1::getNormal(unsigned int idx) const
{
    return (igVec3f *)_vdata[1] + idx;
}

/* A PS2 colour keeps alpha in 0-128: setting halves it (rounding 255 up to 128), reading doubles it back. */

void igPsx2VertexArray1_1::setColor(unsigned int idx, unsigned int abgr)
{
    ((unsigned int *)_vdata[2])[idx] = (abgr & 0xFFFFFF) | (((abgr >> 1) & 0x7F000000) + (abgr & 0x01000000));
}

void igPsx2VertexArray1_1::setColor(unsigned int idx, const igVec4f &rgba)
{
    float scale;
    float a;
    float b;
    float g;
    float r;
    unsigned int alpha;
    unsigned int blue;
    unsigned int green;
    unsigned int red;

    scale = 128.0f;
    a = rgba.vec[3];
    r = rgba.vec[0];
    g = rgba.vec[1];
    b = rgba.vec[2];
    if (!(a <= 1.0f)) {
        scale = 127.9f;
    }
    alpha = (unsigned int)(scale * a) << 24;
    blue = (unsigned int)(255.0f * b) << 16;
    green = (unsigned int)(255.0f * g) << 8;
    red = (unsigned int)(255.0f * r);
    ((unsigned int *)_vdata[2])[idx] = ((alpha | blue) | green) | red;
}

unsigned int igPsx2VertexArray1_1::getColor(unsigned int idx) const
{
    int abgr;
    unsigned int half;

    abgr = ((int *)_vdata[2])[idx];
    half = (unsigned int)(abgr & 0x80000000) >> 7;
    return (abgr & 0xFFFFFF) | (half + (((abgr & 0xFF000000) - half) * 2));
}

void igPsx2VertexArray1_1::getColor(unsigned int idx, igVec4f &rgba) const
{
    unsigned int abgr = ((unsigned int *)_vdata[2])[idx];
    unsigned int channel;
    float value;
    float scale;

    channel = abgr >> 24;
    scale = (channel > 128) ? 0.007843138f : 0.0078125f;
    value = (float)(channel & 0xFF);
    rgba[3] = value * scale;
    channel = (abgr >> 16) & 0xFF;
    value = (float)channel;
    rgba[2] = 0.003921568f * value;
    channel = (abgr >> 8) & 0xFF;
    value = (float)channel;
    rgba[1] = 0.003921568f * value;
    channel = abgr & 0xFF;
    value = (float)channel;
    rgba[0] = 0.003921568f * value;
}

/* Texture coordinate set `which` is stream 11 + which, one igVec2f per vertex. */

void igPsx2VertexArray1_1::setTextureCoord(unsigned int which, unsigned int idx, const igVec2f &coord)
{
    unsigned int stream = which + 11;
    ((igVec2f *)_vdata[stream])[idx] = coord;
}

void igPsx2VertexArray1_1::getTextureCoord(unsigned int which, unsigned int idx, igVec2f &coord) const
{
    unsigned int stream = which + 11;
    coord = ((igVec2f *)_vdata[stream])[idx];
}

const igVec2f *igPsx2VertexArray1_1::getTextureCoord(unsigned int which, unsigned int idx) const
{
    unsigned int stream = which + 11;
    return (igVec2f *)_vdata[stream] + idx;
}

void igPsx2VertexArray1_1::setPointSpriteRadian(unsigned int idx, float radian)
{
    float angle = fmodf(radian, 6.2831855f);

    if (_dpflt(fptodp(angle), 0.0) != 0) {
        angle += 6.2831855f;
    }
    if (!(radian < 0.0f) && radian <= 1.5707964f) {
        ((float *)_vdata[19])[idx] = angle;
    } else if (!(radian <= 1.5707964f) && radian <= 4.712389f) {
        ((float *)_vdata[19])[idx] = 4.712389f - (angle - 1.5707964f);
    } else {
        ((float *)_vdata[19])[idx] = angle - 6.2831855f;
    }
}

float igPsx2VertexArray1_1::getPointSpriteRadian(unsigned int idx) const
{
    float radian = ((float *)_vdata[19])[idx];

    if (!(radian <= 1.5707964f) && (radian <= 4.712389f)) {
        return 4.712389f - (radian - 1.5707964f);
    }
    if (radian < 0.0f) {
        radian += 6.2831855f;
    }
    return radian;
}

/* Points the edit record at component `component` (weights and indices: entry `firstVertex` of each vertex) from
 * vertex `componentIndex` on, with the stream's stride. A dynamic array first waits for its last DMA upload. */
void igPsx2VertexArray1_1::getEditableComponent(igVertexArrayLock *componentInfo, unsigned int editFlags)
{
    int offset;
    int type;
    int start;
    unsigned char *indices;
    int which;

    if (componentInfo->count == 0) {
        componentInfo->count = _numVerts - componentInfo->componentIndex;
    }
    type = componentInfo->component;
    which = componentInfo->firstVertex;
    start = componentInfo->componentIndex;
    switch (type) {
    case 0:
        componentInfo->data = (char *)((igVec3f *)_vdata[0] + componentInfo->getComponentIndex());
        componentInfo->stride = 12;
        break;
    case 1:
        componentInfo->data = (char *)((igVec3f *)_vdata[1] + componentInfo->getComponentIndex());
        componentInfo->stride = 12;
        break;
    case 2:
        componentInfo->data = (char *)((unsigned int *)_vdata[2] + componentInfo->getComponentIndex());
        componentInfo->stride = 4;
        break;
    case 4: {
        int count = getVertexFormat().getBlendWeightCount();
        offset = (which + start * count) * 4;
        componentInfo->data = (char *)_blendWeights + offset;
        componentInfo->stride = count * 4;
        break;
    }
    case 5: {
        int count = getVertexFormat().getBlendIndexCount();
        indices = _blendIndices;
        componentInfo->data = (char *)(indices + (which + start * count));
        componentInfo->stride = count;
        break;
    }
    case 3: {
        int stream = which + 11;
        componentInfo->data = (char *)((igVec2f *)_vdata[stream] + componentInfo->getComponentIndex());
        componentInfo->stride = 8;
        break;
    }
    case 6:
        componentInfo->data = (char *)((float *)_vdata[15] + componentInfo->getComponentIndex());
        componentInfo->stride = getVertexFormat().getPointSpriteCoordCount() * 4;
        break;
    case 9:
        componentInfo->data = (char *)((float *)_vdata[15] + componentInfo->getComponentIndex());
        componentInfo->stride = 4;
        break;
    case 7:
        componentInfo->data = (char *)((igVec3f *)_vdata[17] + componentInfo->getComponentIndex());
        componentInfo->stride = 12;
        break;
    case 8:
        componentInfo->data = (char *)((igVec3f *)_vdata[18] + componentInfo->getComponentIndex());
        componentInfo->stride = 12;
        break;
    }
    componentInfo->reserved = 0;
    if (_usageFlags & 4) {
        p2WaitDmaSequence(1, _lSequence);
    }
}

void igPsx2VertexArray1_1::commitComponentEdits(const igVertexArrayLock &componentInfo, unsigned int commitFlags)
{

}

void igPsx2VertexArray1_1::userApplyWriteProxy(int value)
{
    unsigned int i;
    unsigned int *color;
    unsigned int abgr;
    unsigned int half;

    if (_usageFlags & 4) {
        p2WaitDmaSequence(1, _lSequence);
    }
    freeBlendedVertexLists();
    if (_vertexFormat.hasVertexColors()) {
        color = (unsigned int *)_vdata[2];
        for (i = 0; i < _numVerts; i++) {
            abgr = *color;
            half = (abgr & 0x80000000) >> 7;
            *color = (abgr & 0xffffff) | (half + (((abgr & 0xff000000) - half) * 2));
            color++;
        }
    }
}

void igPsx2VertexArray1_1::userMakeConcrete(igMetaObject *meta)
{
    unsigned int i;
    unsigned int *color;
    unsigned int abgr;

    checkVDataSize();
    if (igVertexArray::getClassMeta() == meta) {
        igVertexArray1_1::userMakeConcrete(meta);
    }
    allocateBlendedVertexLists();
    if (_vertexFormat.hasVertexColors()) {
        color = (unsigned int *)_vdata[2];
        for (i = 0; i < _numVerts; i++) {
            abgr = *color;
            *color = (abgr & 0xFFFFFF) | (((abgr >> 1) & 0x7F000000) + (abgr & 0x01000000));
            color += 1;
        }
    }
}
}
}

