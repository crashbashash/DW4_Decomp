/* IgPrimLengthArray1_1 slot 20, an empty override (`jr ra; nop`). The slot does nothing for this
 * class. */

void igPrimLengthArray1_1_UserMakeConcrete(igPrimLengthArray1_1 *self) {
}

igVertexArrayLock *igVertexArrayLock_Init(igVertexArrayLock *lock) {
    lock->firstVertex = 0;
    lock->component = 0;
    lock->componentIndex = 0;
    lock->count = 0;
    lock->data = 0;
    lock->stride = 0;
    lock->reserved = 0;
    return lock;
}

namespace Gap {
namespace Gfx {

void igVertexArray1_1::resetFields(int flag)
{
    igVertexArray::resetFields(flag);
    _memPool = (igMemoryPool *)getMemoryPool();
}

void igVertexArray1_1::userRegister()
{
    igResource_AddAlignment((igResource *)g_globalContext, "VertexArrayData", 0x10);
    ((igMemoryRefMetaField *)k_blendWeights)->setAlignmentType("VertexArrayData");
}

void igVertexArray1_1::checkVDataSize()
{
    unsigned int size;
    int missing;

    if (_vdata != 0) {
        size = Memory_GetBufferSize(_vdata);
        missing = 0x50 - size;
        if (missing > 0) {
            _vdata = (void **)realloc(_vdata, 0x50);
            memset((char *)_vdata + size, 0, missing);
        }
    }
    if (_memPool == 0) {
        _memPool = (igMemoryPool *)getMemoryPool();
    }
}
}
}

/* Population count. */
int FUN_0015e130(unsigned int v)
{
    int n = 0;
    while (v) {
        if (v & 1)
            n++;
        v >>= 1;
    }
    return n;
}

/* The vertex format a pre-1.1 vertex array's `_vtype` word describes: two bits each for positions and normals,
 * four for colours, and one bit per texture coordinate set, blend weight and blend index. */
igVertexFormat FUN_0015e160(unsigned int vtype) {
    unsigned int flags;
    unsigned int count;
    flags = 0;
    if (vtype & 3) {
        flags |= 1;
    } else {
        flags &= ~1;
    }
    if (vtype & 0xC) {
        flags |= 2;
    } else {
        flags &= ~2;
    }
    if (vtype & 0xF0) {
        flags |= 4;
    } else {
        flags &= ~4;
    }
    count = FUN_0015e130(vtype & 0xF0000);
    count &= 0xFF;
    count <<= 16;
    flags &= 0xFFF0FFFF;
    flags |= count;
    count = FUN_0015e130(vtype & 0xF00);
    count &= 0xFF;
    count <<= 4;
    flags &= ~0xF0;
    flags |= count;
    count = FUN_0015e130(vtype & 0xF000);
    count &= 0xFF;
    count <<= 8;
    flags &= ~0xF00;
    flags |= count;
    return igVertexFormat(flags);
}

namespace Gap {
namespace Gfx {

unsigned int igVertexArray1_1::configure(unsigned int vertexFormatFlags, unsigned int vertexCount, unsigned int usageFlags, igVisualContext *context)
{
    igVertexFormat vertexFormat = FUN_0015e160(vertexFormatFlags);
    return configure(vertexFormat, vertexCount, usageFlags, context);
}

/* Moves a pre-1.1 array's per-weight and per-index streams (3-6 and 7-10) into the interleaved _blendWeights and
 * _blendIndices, and its `_vtype` word into _vertexFormat. */
void igVertexArray1_1::userMakeConcrete(igMetaObject *meta)
{
    /* matching construct: declaration-order sweep (an unsigned int count, this order) gives retail's registers;
     * retail takes the stream table's address on every pass of the label loops (matching-decomp.md) */
    unsigned int count;
    unsigned int i;
    void *source;
    unsigned int vertexCount;
    void ***streams;
    igVertexFormat vertexFormat = FUN_0015e160(_vtype);
    unsigned int j;
    int offset;

    _vertexFormat = vertexFormat;
    _vtype = 0;
    if (_memPool == 0) {
        _memPool = (igMemoryPool *)getMemoryPool();
    }
    count = vertexFormat.getBlendWeightCount();
    vertexCount = _numVerts;
    if (count != 0) {
        _blendWeights = (float *)((igMemoryPoolView *)_memPool.p)->allocateAligned(vertexCount * (count * 4), 0x10);
        i = 0;
        goto testWeights;
    weights:
        streams = &_vdata;
        offset = (i + 3) * sizeof(void *);
        source = *(void **)((char *)_vdata + offset);
        for (j = 0; j < vertexCount; j++) {
            _blendWeights[i + count * j] = ((float *)source)[j];
        }
        Memory_FreeBuffer(source);
        *(void **)((char *)*streams + offset) = 0;
        i++;
    testWeights:
        if (i < count) goto weights;
    }
    count = vertexFormat.getBlendIndexCount();
    if (count != 0) {
        _blendIndices = (unsigned char *)((igMemoryPoolView *)_memPool.p)->allocateAligned(count * vertexCount, 0x10);
        i = 0;
        goto testIndices;
    indices:
        streams = &_vdata;
        offset = (i + 7) * sizeof(void *);
        source = *(void **)((char *)_vdata + offset);
        for (j = 0; j < vertexCount; j++) {
            _blendIndices[i + count * j] = ((unsigned char *)source)[j];
        }
        Memory_FreeBuffer(source);
        *(void **)((char *)*streams + offset) = 0;
        i++;
    testIndices:
        if (i < count) goto indices;
    }
}

void igVertexArray1_1::cache()
{
}

unsigned int igVertexArray1_1::allocateAbstractVertexArrayMemory()
{
    unsigned int total;
    unsigned int size;
    unsigned int i;

    total = 0;
    const igVertexFormat &vertexFormat = getVertexFormat();
    if (_memPool == 0) {
        _memPool = (igMemoryPool *)getMemoryPool();
    }
    if (vertexFormat.hasPositions()) {
        size = _numVerts * 12;
        _vdata[0] = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    if (vertexFormat.hasNormals()) {
        size = _numVerts * 12;
        if (vertexFormat.hasBinormals() || vertexFormat.hasTangents()) {
            size += _numVerts * 24;
        }
        _vdata[1] = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    if (vertexFormat.hasVertexColors()) {
        size = _numVerts * 4;
        _vdata[2] = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    if (vertexFormat.getBlendWeightCount() != 0) {
        size = _numVerts * vertexFormat.getBlendWeightCount() * 4;
        total += size;
        if (_blendWeights == 0) {
            _blendWeights = (float *)((igMemoryPoolView *)_memPool.p)->allocateAligned(size, 0x10);
        }
    }
    if (vertexFormat.getBlendIndexCount() != 0) {
        size = _numVerts * vertexFormat.getBlendIndexCount();
        total += size;
        if (_blendIndices == 0) {
            _blendIndices = (unsigned char *)((igMemoryPoolView *)_memPool.p)->allocateAligned(size, 0x10);
        }
    }
    for (i = 0; i < vertexFormat.getTextureCoordCount(); i++) {
        unsigned int stream = i + 11;
        size = _numVerts * 8;
        _vdata[stream] = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    total += allocatePointSpriteMemory();
    total += allocateAbstractBiNormalsAndTangentsMemory();
    return total;
}

const igVertexFormat &igVertexArray1_1::getVertexFormat() const
{
    return _vertexFormat;
}

void igVertexArray1_1::freeAbstractVertexArrayMemory()
{
    unsigned int i;
    void ***streams;
    void *stream;
    const igVertexFormat &vertexFormat = getVertexFormat();
    void ***coordStreams;
    unsigned int index;

    if (vertexFormat.hasPositions()) {
        streams = &_vdata;
        stream = (*streams)[0];
        if (stream != 0) {
            Memory_FreeBuffer(stream);
            (*streams)[0] = 0;
        }
    }
    if (vertexFormat.hasNormals()) {
        streams = &_vdata;
        stream = (*streams)[1];
        if (stream != 0) {
            Memory_FreeBuffer(stream);
            (*streams)[1] = 0;
        }
    }
    if (vertexFormat.hasVertexColors()) {
        streams = &_vdata;
        stream = (*streams)[2];
        if (stream != 0) {
            Memory_FreeBuffer(stream);
            (*streams)[2] = 0;
        }
    }
    if (_blendWeights != 0) {
        Memory_FreeBuffer(_blendWeights);
        _blendWeights = 0;
    }
    if (_blendIndices != 0) {
        Memory_FreeBuffer(_blendIndices);
        _blendIndices = 0;
    }
    /* matching construct: retail takes the stream table's address on every pass (matching-decomp.md) */
    i = 0;
    goto test;
top:
    index = i + 11;
    coordStreams = &_vdata;
    stream = (*coordStreams)[index];
    if (stream != 0) {
        Memory_FreeBuffer(stream);
        (*coordStreams)[index] = 0;
    }
    i++;
test:
    if (i < vertexFormat.getTextureCoordCount()) goto top;
    freePointSpriteMemory();
    freeAbstractBiNormalsAndTangentsMemory();
}

void igVertexArray1_1::setWeight(unsigned int which, unsigned int idx, float weight)
{
    float *weights = _blendWeights;
    weights[which + idx * getVertexFormat().getBlendWeightCount()] = weight;
}

float igVertexArray1_1::getWeight(unsigned int which, unsigned int idx) const
{
    float *weights = _blendWeights;
    return weights[which + idx * getVertexFormat().getBlendWeightCount()];
}

void igVertexArray1_1::validateBlendWeights()
{
    unsigned int count;
    float *weights;
    unsigned int i;
    unsigned int j;
    unsigned int first;
    float sum;
    float last;

    count = getVertexFormat().getBlendWeightCount();
    if (count != 0) {
        weights = _blendWeights;
        for (i = 0; i < _numVerts; i++) {
            first = i * count;
            sum = 0.0f;
            for (j = 0; j + 1 < count; j++) {
                sum += weights[j + first];
            }
            last = 1.0f - sum;
            if (last < 0.0f) {
                last = 0.0f;
            }
            weights[count + first - 1] = last;
        }
    }
}

void igVertexArray1_1::setBlendMatrixIndex(unsigned int which, unsigned int idx, unsigned char matrixIndex)
{
    unsigned char *indices = _blendIndices;
    indices[which + idx * getVertexFormat().getBlendWeightCount()] = matrixIndex;
}

unsigned char igVertexArray1_1::getBlendMatrixIndex(unsigned int which, unsigned int idx) const
{
    unsigned char *indices = _blendIndices;
    return indices[which + idx * getVertexFormat().getBlendWeightCount()];
}

void igVertexArray1_1::setPointSpriteSize(unsigned int idx, float size)
{
    ((float *)_vdata[15])[idx] = 0.5f * size;
}

float igVertexArray1_1::getPointSpriteSize(unsigned int idx) const
{
    return 2.0f * ((float *)_vdata[15])[idx];
}

void igVertexArray1_1::setPointSpriteSize(unsigned int idx, igVec2f size)
{
    float width = size[0];
    float height = size[1];
    float *half;

    width = width * 0.5f;
    height = height * 0.5f;
    half = (float *)((igVec2f *)_vdata[15] + idx);
    half[0] = width;
    half[1] = height;
}

void igVertexArray1_1::getPointSpriteSize(unsigned int idx, igVec2f &size) const
{
    float scale = 2.0f;

    size = ((igVec2f *)_vdata[15])[idx];
    size[0] = size[0] * scale;
    size[1] = size[1] * scale;
}

void igVertexArray1_1::setPointSpriteRadian(unsigned int idx, float size)
{
    ((float *)_vdata[19])[idx] = size;
}

float igVertexArray1_1::getPointSpriteRadian(unsigned int idx) const
{
    return ((float *)_vdata[19])[idx];
}

unsigned int igVertexArray1_1::reconfigure(const igVertexFormat &vertexFormat, unsigned int vertexCount, unsigned int usageFlags, igVisualContext *context)
{
    igSmartPointer<igVertexArray1_1> resized(_instantiateFromPool(getMemoryPool()));
    unsigned int count;
    unsigned int result;
    unsigned int i;

    resized->_memPool = _memPool;
    result = resized->configure(vertexFormat, vertexCount, usageFlags, context);
    count = _numVerts;
    count = (count < vertexCount) ? count : vertexCount;
    igVertexFormat common = vertexFormat & getVertexFormat();
    for (i = 0; i < count; i++) {
        FUN_0015dbc0((igVertexArrayAccess *)resized.p, i, (igVertexArrayAccess *)this, i, &common);
    }
    resized->validateBlendWeights();
    resized->userApplyWriteProxy((int)_Meta);
    userApplyWriteProxy((int)_Meta);
    freeAbstractVertexArrayMemory();
    Memory_FreeBuffer(_vdata);
    _numVerts = vertexCount;
    _vdata = resized->_vdata;
    _blendWeights = resized->_blendWeights;
    _blendIndices = resized->_blendIndices;
    _blendIndex = resized->_blendIndex;
    _vertexFormat = resized->_vertexFormat;
    _memPool = resized->_memPool;
    resized->_numVerts = 0;
    resized->_vdata = 0;
    resized->_blendWeights = 0;
    resized->_blendIndices = 0;
    resized->_blendIndex = 0;
    resized->_vertexFormat.clear();
    userMakeConcrete(_Meta);
    cache();
    return result;
}

/* Binormals (stream 17) and tangents (stream 18) are kept only when the vertex format holds them. */

void igVertexArray1_1::setBinormal(unsigned int idx, const igVec3f &binormal)
{
    if (_vertexFormat.hasBinormals()) {
        ((igVec3f *)_vdata[17])[idx] = binormal;
    }
}

void igVertexArray1_1::getBinormal(unsigned int idx, igVec3f &binormal) const
{
    if (_vertexFormat.hasBinormals()) {
        binormal = ((igVec3f *)_vdata[17])[idx];
    }
}

const igVec3f *igVertexArray1_1::getBinormal(unsigned int idx) const
{
    if (_vertexFormat.hasBinormals()) {
        return (igVec3f *)_vdata[17] + idx;
    }
    return 0;
}

void igVertexArray1_1::setTangent(unsigned int idx, const igVec3f &tangent)
{
    if (_vertexFormat.hasTangents()) {
        ((igVec3f *)_vdata[18])[idx] = tangent;
    }
}

void igVertexArray1_1::getTangent(unsigned int idx, igVec3f &tangent) const
{
    if (_vertexFormat.hasTangents()) {
        tangent = ((igVec3f *)_vdata[18])[idx];
    }
}

const igVec3f *igVertexArray1_1::getTangent(unsigned int idx) const
{
    if (_vertexFormat.hasTangents()) {
        return (igVec3f *)_vdata[18] + idx;
    }
    return 0;
}

void igVertexArray1_1::freePointSpriteMemory()
{
    void **&streams = _vdata;

    if (streams[16] != 0) {
        Memory_FreeBuffer(streams[16]);
        streams[16] = 0;
    }
    if (streams[15] != 0) {
        Memory_FreeBuffer(streams[15]);
        streams[15] = 0;
    }
    if (streams[19] != 0) {
        Memory_FreeBuffer(streams[19]);
        streams[19] = 0;
    }
}

unsigned int igVertexArray1_1::allocatePointSpriteMemory()
{
    unsigned int total;
    unsigned int size;
    unsigned char count;
    void **stream;

    igVertexFormat vertexFormat = getVertexFormat();
    count = vertexFormat.getPointSpriteCoordCount();
    total = 0;
    if (count != 0) {
        /* matching construct: retail zero-extends the count a second time before the multiply */
        size = _numVerts * ((count & 0xFF) * sizeof(float));
        stream = &_vdata[15];
        *stream = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    void **&streams = _vdata;
    streams[16] = 0;
    if (vertexFormat.hasSpriteRadians()) {
        size = _numVerts * 4;
        stream = &streams[19];
        *stream = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    return total;
}

void igVertexArray1_1::freeAbstractBiNormalsAndTangentsMemory()
{
    void **&streams = _vdata;

    if (streams[17] != 0) {
        Memory_FreeBuffer(streams[17]);
        streams[17] = 0;
    }
    if (streams[18] != 0) {
        Memory_FreeBuffer(streams[18]);
        streams[18] = 0;
    }
}

unsigned int igVertexArray1_1::allocateAbstractBiNormalsAndTangentsMemory()
{
    unsigned int total;
    void **stream;
    unsigned int size;

    igVertexFormat vertexFormat = getVertexFormat();
    total = 0;
    if (vertexFormat.hasBinormals()) {
        stream = &_vdata[17];
        size = _numVerts * 12;
        *stream = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    if (vertexFormat.hasTangents()) {
        stream = &_vdata[18];
        size = _numVerts * 12;
        *stream = ((igMemoryPoolView *)_memPool.p)->malloc(size);
        total += size;
    }
    return total;
}
}
}

static int FUN_0015f430(void *arg0, int arg1, int arg2, int arg3) { if (arg1 == *(int *)((char *)(arg0) + 16)) { if (arg2 == *(int *)((char *)(arg0) + 20)) { return 1; } } return 0; }

static int FUN_0015f460(void *arg0, int arg1, int arg2, int arg3)
{
  if (arg1 == (*((int *) (((char *) arg0) + 16))))
  {
    if ((arg3 == (*((int *) (((char *) arg0) + 28)))) && (arg2 == (*((int *) (((char *) arg0) + 20)))))
    {
      return 1;
      return 0;
    }
  }
  return 0;
}

int *FUN_0015f4a0(struct S_15f430 *s, int a1, unsigned int a2) {
    int *found = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        int *item = s->items[i];
        if (FUN_0015f430(item, a1, a2, 0) != 0) { found = item; break; }
    }
    return found;
}

void *FUN_0015f510(L *l, int a1, int a2, int a3) {
  void *r = 0; int i; void *e;
  for (i = 0; i < l->n; i++) { e = (void*)l->data[i]; if (FUN_0015f460(e, a1, a3, a2)) { r = e; break; } }
  return r; }

