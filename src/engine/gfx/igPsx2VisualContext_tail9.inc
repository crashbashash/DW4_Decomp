namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setBlendingMatrices(const unsigned int matrixCount, const igMatrix44f *matrixArray) {
    _blendMatricesCount = matrixCount;
    _blendMatrices = matrixArray;
    _inverseTransposeNeedValidation = 1;
    _blendIndex = _blendIndex + 1;
    p2SetBlendMatrices((int)_blendMatrices, _blendMatricesCount);
}
}
}

/* Rebuilds the inverse-transpose of every blend matrix (the inverse with its translation cleared, then
 * transposed), growing the driver-data array first when the matrix count outgrew it. */
void FUN_00180060(igPsx2VisualContext *vc) {
    int zeroTranslation[3];
    float *inverse;
    unsigned int i;
    if (vc->_blendMatrices != 0) {
        if (vc->_inverseTransposeCount_ < (int)vc->_blendMatricesCount) {
            if (vc->_inverseTranspose != 0) {
                ((igMemoryPoolView *)((Gap::Gfx::igVisualContext *)vc)->getDriverDataMemoryPool())->Free((void *)vc->_inverseTranspose);
                vc->_inverseTranspose = 0;
            }
            vc->_inverseTranspose = (int)((igMemoryPoolView *)((Gap::Gfx::igVisualContext *)vc)->getDriverDataMemoryPool())->AllocateAligned(vc->_blendMatricesCount << 6, 0x10);
            vc->_inverseTransposeCount_ = vc->_blendMatricesCount;
        }
        for (i = 0; i < (unsigned int)vc->_blendMatricesCount; i++) {
            inverse = (float *)(vc->_inverseTranspose + (i << 6));
            igMatrix44f_Invert(inverse, (const float *)(vc->_blendMatrices + (i << 6)));
            zeroTranslation[0] = 0;
            zeroTranslation[1] = 0;
            zeroTranslation[2] = 0;
            igMatrix44f_SetTranslation(inverse, (float *)zeroTranslation);
            FUN_001903d0(inverse);
        }
    }
    vc->_inverseTransposeNeedValidation = 0;
}

/* A new vertex data, its reference adopted: the old one is released first. */
static inline void createOwned(igSmartPointer<igVertexData> &holder, AdoptReference) {
    igVertexData *old = holder.p;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    holder.p = (igVertexData *)igVertexData_Create(0);
}

/* Makes `list` the component list of `owner`, taking a counted reference to it. */
static inline void setComponentList(const igSmartPointer<igVertexData> &owner, const igSmartPointer<igVec3fList> &list) {
    igVec3fList *held = list.p;
    igVertexData *target = owner.p;
    igObject *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = (igObject *)target->_data;
    igObject::release(old);
    target->_data = (int)held;
}

/* Blends the stream's vertices on the CPU. The blend writes into position (and, with lighting or texture
 * generation, normal) components carrying the user ID 0x7734; the stream gets a vertex data for each when it
 * has none, the inverse-transpose matrices are refreshed for the normals, and the weights and indices go to the
 * blend routine. */
void FUN_001805a0(igPsx2VisualContext *vc, Gap::Gfx::igPsx2VertexStream *stream, int count) {
    igVertexData *srcNormals;
    igVertexData *indices;
    igVertexData *srcPositions;
    igVertexDataList *list;
    igVertexData *weights;
    list = (igVertexDataList *)stream->_vertexDataList.p;
    srcNormals = 0;
    igSmartPointer<igVertexData> outPositions((igVertexData *)0, kRetainReference);
    igSmartPointer<igVertexData> outNormals((igVertexData *)0, kRetainReference);
    weights = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_WEIGHT, 0);
    indices = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_INDEX, 0);
    if (vc->_bLightingEnabled != 0 || vc->_texCoordSource[0] == 2) {
        if (vc->_inverseTransposeNeedValidation != 0) FUN_00180060(vc);
        outNormals = FUN_0015f510(list, IG_VERTEX_COMPONENT_NORMAL, 0, 0x7734);
        if (outNormals.p == 0) {
            igSmartPointer<igVec3fList> values(igVec3fList_Create(0), AdoptReference());
            ((Gap::Core::igTDataList<igVec3f> *)values.p)->setCount(count);
            createOwned(outNormals, AdoptReference());
            setComponentList(outNormals, values);
            outNormals.p->_componentType = IG_VERTEX_COMPONENT_NORMAL;
            outNormals.p->_userID = 0x7734;
            ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)outNormals.p);
            srcNormals = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_NORMAL, 0);
            srcNormals->_componentIndex = 0x7734;
        } else {
            srcNormals = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_NORMAL, 0x7734);
        }
    }
    outPositions = FUN_0015f510(list, IG_VERTEX_COMPONENT_POSITION, 0, 0x7734);
    if (outPositions.p == 0) {
        igSmartPointer<igVec3fList> values(igVec3fList_Create(0), AdoptReference());
        ((Gap::Core::igTDataList<igVec3f> *)values.p)->setCount(count);
        createOwned(outPositions, AdoptReference());
        setComponentList(outPositions, values);
        outPositions.p->_componentType = IG_VERTEX_COMPONENT_POSITION;
        outPositions.p->_userID = 0x7734;
        ((Gap::Core::igObjectList *)list)->append((Gap::Core::igObject *)outPositions.p);
        srcPositions = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_POSITION, 0);
        srcPositions->_componentIndex = 0x7734;
    } else {
        srcPositions = FUN_0015f4a0(list, IG_VERTEX_COMPONENT_POSITION, 0x7734);
    }
    stream->waitForSync();
    FUN_00180ab0(vc, srcPositions, outPositions.p, srcNormals, outNormals.p, weights, indices, Gap::Gfx::igVertexArray2Helper::getIndexCount(indices));
}
