namespace Gap {
namespace Attrs {

unsigned int igGeometryAttr::getPrimitiveLength(unsigned int i) const
{
    if (_primLengths != 0) {
        return _primLengths->get(i);
    }
    return 0;
}

void igGeometryAttr1_5::synchronizeDefault(igVisualContext *visualContext)
{
    igGeometryAttr::synchronizeDefault(visualContext);
}

unsigned int igGeometryAttr1_5::configureVertexArray(const igVertexFormat &vertexFormat, unsigned int vertexCount, unsigned int usage, igVisualContext *context)
{
    if (_vertexArray == 0) {
        _vertexArray = igVertexArray::_instantiateFromPool(getMemoryPool());
        _vertexArray->release();
    }
    return _vertexArray->configure(vertexFormat, vertexCount, usage, context);
}

void igGeometryAttr1_5::userMakeConcrete(igMetaObject *meta)
{
    int i;

    if (igGeometryAttr::getClassMeta() == meta && _primLengths != 0) {
        /* matching construct: retail releases the old array here without clearing the field (a store of 0 adds a
         * `sw zero,48(s1)`); the assignment below releases the same pointer once more */
        _stripLengths.release();
        _stripLengths = igSmartPointer<igPrimLengthArray>(igPrimLengthArray::_instantiateFromPool(getMemoryPool()));
        _stripLengths->configure(_primLengths->getCount(), 32, 0);
        for (i = 0; i < _primLengths->getCount(); i++) {
            igGeometryAttr1_5::setPrimitiveLength(i, igGeometryAttr::getPrimitiveLength(i));
        }
    }
}

void igGeometryAttr1_5::apply(igVisualContext *vc)
{
    /* matching construct: declaration and load order permutation sweep (5040 + 120 variants) */
    int primType;
    unsigned int numPrims;
    unsigned int offset;
    int drawMultiple;
    igIndexArray *indexArray;
    int overlap;
    igPrimLengthArray *lengths;

    igPsx2VisualContext_SetVertexArray((igPsx2VisualContext *)vc, (::igVertexArray *)_vertexArray.p);
    offset = _offset;
    numPrims = _numPrims;
    primType = _primType;
    lengths = _stripLengths;
    indexArray = _indexArray;
    if (indexArray != 0) {
        igPsx2VisualContext_SetIndexArray((igPsx2VisualContext *)vc, (::igIndexArray *)indexArray);
    }
    if (lengths != 0) {
        if (primType == IG_GFX_DRAW_LINE_STRIP) {
            drawMultiple = IG_GFX_DRAW_MULTIPLE_LINE_STRIPS;
            overlap = 1;
        } else if (primType == IG_GFX_DRAW_TRIANGLE_STRIP) {
            drawMultiple = IG_GFX_DRAW_MULTIPLE_TRIANGLE_STRIPS;
            overlap = 2;
        } else {
            if (primType != IG_GFX_DRAW_TRIANGLE_FAN) {
                return;
            }
            drawMultiple = IG_GFX_DRAW_MULTIPLE_TRIANGLE_FANS;
            overlap = 2;
        }
        switch (numPrims) {
        case 0:
            break;
        case 1:
            igPsx2VisualContext_Draw((igPsx2VisualContext *)vc, primType, lengths->getPrimLength(0) - overlap, offset);
            break;
        default:
            igPsx2VisualContext_SetPrimLengthArray((igPsx2VisualContext *)vc, (::igPrimLengthArray *)lengths);
            igPsx2VisualContext_DrawMultiple((igPsx2VisualContext *)vc, drawMultiple, numPrims, offset, 0);
        }
        if (lengths != 0) {
            igPsx2VisualContext_SetPrimLengthArray((igPsx2VisualContext *)vc, 0);
        }
    } else {
        igPsx2VisualContext_Draw((igPsx2VisualContext *)vc, primType, numPrims, offset);
    }
    if (indexArray != 0) {
        igPsx2VisualContext_SetIndexArray((igPsx2VisualContext *)vc, 0);
    }
}
}
}

namespace Gap {
namespace Attrs {

bool igGeometryAttr1_5::configurePrimitive(IG_GFX_DRAW type, unsigned int num, unsigned int offset)
{
    _primType = type;
    _numPrims = num;
    _offset = offset;
    if (_primType == IG_GFX_DRAW_TRIANGLE_STRIP || _primType == IG_GFX_DRAW_TRIANGLE_FAN || _primType == IG_GFX_DRAW_LINE_STRIP) {
        if (_stripLengths == 0) {
            _stripLengths = igSmartPointer<igPrimLengthArray>(igPrimLengthArray::_instantiateFromPool(getMemoryPool()));
        }
        if (_stripLengths->getCount() < num) {
            _stripLengths->configure(num, 32, 0);
        }
    }
    return true;
}
}
}

/* Position of vertex `index` in a locked vertex component. */
static inline float *lockedVertex(const igVertexArrayLock &lock, unsigned int index) {
    return (float *)(lock.data + index * lock.stride);
}

namespace Gap {
namespace Attrs {

/* Ray test over the triangles of a triangle list (type 3) or triangle strips (type 4), plain or indexed. Each
 * triangle goes through FUN_0018b9e0; the first hit after (*primIndex, *vertexIndex) wins, and that position is
 * written back, so a caller passing `resume` walks every hit in turn. */
bool igGeometryAttr1_5::intersectRay(const igRay *ray, igVec3f &intersectPoint, igVec3f &norm, int &primIndex, int &polyIndex, ISET_SIDES whichFaces, bool findNextIntersection)
{
    igVertexArrayLock lock;
    int prim = 0;
    int vertex = 0;
    unsigned short *indices;
    /* matching construct: the strip corners a, b, c are function-scope variables shared by both strip loops */
    int a;
    int b;
    int c;
    bool found;
    igVertexArrayLock_Init(&lock);
    indices = 0;
    found = false;
    if (!findNextIntersection || primIndex == -1 || polyIndex == -1) {
        primIndex = -1;
        polyIndex = -1;
    }
    lock.setType(IG_GFX_POSITION);
    lock.componentIndex = _offset;
    lock.count = 0;
    _vertexArray->getEditableComponent(&lock, 0);
    if (_primType == IG_GFX_DRAW_TRIANGLES) {
        if (_indexArray != 0) {
            indices = _indexArray->getEditableIndices16(0, 0, -1);
            for (vertex = 0, prim = 0; prim < lock.count; prim++, vertex += 3) {
                unsigned short *triangle = indices + vertex;
                if (FUN_0018b9e0(ray, lockedVertex(lock, triangle[0]), lockedVertex(lock, triangle[1]),
                                 lockedVertex(lock, triangle[2]), intersectPoint.vec, norm.vec, whichFaces) >= 0.0f &&
                    prim > primIndex) {
                    found = true;
                    break;
                }
            }
        } else {
            for (vertex = 0, prim = 0; prim < lock.count; prim++, vertex += 3) {
                if (FUN_0018b9e0(ray, lockedVertex(lock, vertex), lockedVertex(lock, vertex + 1),
                                 lockedVertex(lock, vertex + 2), intersectPoint.vec, norm.vec, whichFaces) >= 0.0f &&
                    prim > primIndex) {
                    found = true;
                    break;
                }
            }
        }
    } else if (_primType == IG_GFX_DRAW_TRIANGLE_STRIP) {
        if (_indexArray != 0) {
            indices = _indexArray->getEditableIndices16(0, 0, -1);
            int first = 0;
            for (prim = 0; prim < lock.count; prim++) {
                unsigned int length = _stripLengths->getPrimLength(prim);
                a = first;
                b = first + 1;
                for (vertex = 2; vertex < length; vertex++) {
                    c = first + vertex;
                    float t;
                    if (vertex & 1) {
                        t = FUN_0018b9e0(ray, lockedVertex(lock, indices[a]), lockedVertex(lock, indices[c]),
                                         lockedVertex(lock, indices[b]), intersectPoint.vec, norm.vec, whichFaces);
                    } else {
                        t = FUN_0018b9e0(ray, lockedVertex(lock, indices[a]), lockedVertex(lock, indices[b]),
                                         lockedVertex(lock, indices[c]), intersectPoint.vec, norm.vec, whichFaces);
                    }
                    if (t >= 0.0f && (prim > primIndex || (prim == primIndex && vertex > polyIndex))) {
                        found = true;
                        goto done;
                    }
                    a = b;
                    b = c;
                }
                first += length;
            }
        } else {
            int first = 0;
            for (prim = 0; prim < lock.count; prim++) {
                unsigned int length = _stripLengths->getPrimLength(prim);
                a = first;
                b = first + 1;
                for (vertex = 2; vertex < length; vertex++) {
                    c = first + vertex;
                    float t;
                    if (vertex & 1) {
                        t = FUN_0018b9e0(ray, lockedVertex(lock, a), lockedVertex(lock, c), lockedVertex(lock, b),
                                         intersectPoint.vec, norm.vec, whichFaces);
                    } else {
                        t = FUN_0018b9e0(ray, lockedVertex(lock, a), lockedVertex(lock, b), lockedVertex(lock, c),
                                         intersectPoint.vec, norm.vec, whichFaces);
                    }
                    if (t >= 0.0f && (prim > primIndex || (prim == primIndex && vertex > polyIndex))) {
                        found = true;
                        goto done;
                    }
                    a = b;
                    b = c;
                }
                first += length;
            }
        }
    }
    done:
    primIndex = prim;
    polyIndex = vertex;
    _vertexArray->commitComponentEdits(lock, 1);
    if (indices != 0) {
        _indexArray->commitIndexEdits(indices, 1, 0, -1);
    }
    return found;
}

void igGeometryAttr1_5::transformVectors(IG_GFX_VERTEX_COMPONENT component, igVertexArray *vertexArray, const float *matrix)
{
    igVertexArrayLock lock;
    igVertexArrayLock_Init(&lock);
    lock.setType(component);
    vertexArray->getEditableComponent(&lock, 0);
    char *vertex = lock.data;
    for (unsigned int i = 0; i < lock.count; i++) {
        igVec3f *vector = (igVec3f *)vertex;
        FUN_00192360(matrix, vector->vec, vector->vec, 1);
        float length = vector->length();
        if (length > 5e-7f) {
            vector->scale(1.0f / length);
        }
        vertex += lock.stride;
    }
    vertexArray->commitComponentEdits(lock, 0);
}

void igGeometryAttr1_5::transform(const igMatrix44f &m)
{
    /* matching construct: declaration-order sweep — vertex and i declared before format */
    char *vertex;
    unsigned int i;
    igVertexFormat format = _vertexArray->getVertexFormat();

    if (format.hasPositions()) {
        igVertexArrayLock lock;
        igVertexArrayLock_Init(&lock);
        lock.setType(IG_GFX_POSITION);
        lock.componentIndex = _offset;
        lock.count = 0;
        _vertexArray->getEditableComponent(&lock, 0);
        if (lock.stride == 12) {
            FUN_00192430(m.m, (float *)lock.data, (float *)lock.data, lock.count);
        } else {
            vertex = lock.data;
            for (i = 0; i < lock.count; i++) {
                FUN_00192430(m.m, (float *)vertex, (float *)vertex, 1);
                vertex += lock.stride;
            }
        }
        _vertexArray->commitComponentEdits(lock, 0);
    }
    {
        igMatrix44f normalMatrix;
        igMatrix44f_Invert(normalMatrix.m, m.m);
        FUN_001903d0(normalMatrix.m);
        if (format.hasNormals()) {
            transformVectors(IG_GFX_NORMAL, _vertexArray, normalMatrix.m);
        }
        if (format.hasBinormals()) {
            transformVectors(IG_GFX_BINORMAL, _vertexArray, normalMatrix.m);
        }
        if (format.hasTangents()) {
            transformVectors(IG_GFX_TANGENT, _vertexArray, normalMatrix.m);
        }
    }
}

void igGeometryAttr1_5::setPrimitiveLength(unsigned int uiPrim, unsigned int uiLength)
{
    unsigned int count;

    if (_stripLengths == 0) {
        _stripLengths = igSmartPointer<igPrimLengthArray>(igPrimLengthArray::_instantiateFromPool(getMemoryPool()));
    }
    count = uiPrim + 1;
    if (_stripLengths->getCount() < count) {
        _stripLengths->configure(count, 32, 0);
    }
    _stripLengths->setPrimLength(uiPrim, uiLength);
}

unsigned int igGeometryAttr1_5::getNumVerts() const
{
    unsigned int i;
    unsigned int total;
    igPrimLengthArray *lengths;
    int type;
    unsigned int count;
    unsigned int vertexCount;
    unsigned int offset;

    /* matching construct: statement-order sweep — offset read second */
    vertexCount = _vertexArray->getCount();
    offset = _offset;
    count = _numPrims;
    type = _primType;
    lengths = _stripLengths;
    if (_indexArray != 0) {
        total = vertexCount - offset;
    } else {
        total = 0;
        if (type == IG_GFX_DRAW_TRIANGLE_STRIP || type == IG_GFX_DRAW_TRIANGLE_FAN || type == IG_GFX_DRAW_LINE_STRIP) {
            for (i = 0; i < count; i++) {
                total += lengths->getPrimLength(i);
            }
        } else {
            if (type == IG_GFX_DRAW_POINTS) {
                total = count;
            } else {
                if (type == IG_GFX_DRAW_LINES) {
                    count *= 2;
                } else if (type == IG_GFX_DRAW_TRIANGLES) {
                    count *= 3;
                } else {
                    count = 0;
                }
                total = count;
            }
        }
    }
    return total;
}

static inline float vertexComponent(const igVec3f *vertex, int index) { return vertex->vec[index]; }

void igGeometryAttr1_5::computeBound(igVec3f *min, igVec3f *max)
{
    igVertexArrayLock lock;
    float mz = 1e20f;
    float my = mz;
    float mx = mz;
    float nz = -1e20f;
    float ny = nz;
    float nx = nz;
    unsigned int i;

    igVertexArrayLock_Init(&lock);
    lock.setType(IG_GFX_POSITION);
    lock.componentIndex = _offset;
    lock.count = 0;
    _vertexArray->getEditableComponent(&lock, 0);
    for (i = 0; i < lock.count; i++) {
        igVec3f *p = (igVec3f *)(lock.data + i * lock.stride);
        if (!(mx <= p->vec[0])) { mx = p->vec[0]; }
        if (!(my <= p->vec[1])) { my = p->vec[1]; }
        if (!(mz <= p->vec[2])) { mz = p->vec[2]; }
        /* matching construct: the maximum reads each component through an accessor (retail reloads it; a plain
         * read is shared with the minimum's) */
        { float t = vertexComponent(p, 0); if (nx < t) { nx = t; } }
        { float t = vertexComponent(p, 1); if (ny < t) { ny = t; } }
        { float t = vertexComponent(p, 2); if (nz < t) { nz = t; } }
    }
    (*min)[0] = mx;
    (*min)[1] = my;
    (*min)[2] = mz;
    (*max)[0] = nx;
    (*max)[1] = ny;
    (*max)[2] = nz;
    _vertexArray->commitComponentEdits(lock, 0);
}

void igGeometryAttr1_5::userPostLoad()
{
    unsigned int count;
    unsigned int i;

    igAttr::userPostLoad();
    if (_dPds != 0 || _dPdt != 0) {
        igVertexFormat vertexFormat = _vertexArray->getVertexFormat();
        if (_dPdt != 0) {
            vertexFormat.setHasBinormals(true);
        } else {
            vertexFormat.setHasBinormals(false);
        }
        if (_dPds != 0) {
            vertexFormat.setHasTangents(true);
        } else {
            vertexFormat.setHasTangents(false);
        }
        count = _vertexArray->getCount();
        _vertexArray->reconfigure(vertexFormat, count, _vertexArray->getUsageFlags(), 0);
        i = 0;
        if (_dPdt != 0) {
            for (; i < count; i++) {
                _vertexArray->setBinormal(i, ((igVec3f *)_dPdt->_data)[i]);
            }
            _dPdt = 0;
        }
        i = 0;
        if (_dPds != 0) {
            for (; i < count; i++) {
                _vertexArray->setTangent(i, ((igVec3f *)_dPds->_data)[i]);
            }
            _dPds = 0;
        }
    }
}

igResult igGeometryAttr1_5::setTangents(igVec3fList *tangents)
{
    unsigned int count;
    unsigned int i;

    count = tangents->_count;
    if (_vertexArray->getCount() < count) {
        return g_resultFailure;
    }
    igVertexFormat vertexFormat = _vertexArray->getVertexFormat();
    if (!vertexFormat.hasTangents()) {
        vertexFormat.setHasTangents(true);
        _vertexArray->reconfigure(vertexFormat, _vertexArray->getCount(), _vertexArray->getUsageFlags(), 0);
    }
    for (i = 0; i < count; i++) {
        _vertexArray->setTangent(i, ((igVec3f *)tangents->_data)[i]);
    }
    return g_resultSuccess;
}

igResult igGeometryAttr1_5::setBinormals(igVec3fList *bn)
{
    unsigned int count;
    unsigned int i;

    count = bn->_count;
    if (_vertexArray->getCount() < count) {
        return g_resultFailure;
    }
    igVertexFormat vertexFormat = _vertexArray->getVertexFormat();
    if (!vertexFormat.hasBinormals()) {
        vertexFormat.setHasBinormals(true);
        _vertexArray->reconfigure(vertexFormat, _vertexArray->getCount(), _vertexArray->getUsageFlags(), 0);
    }
    for (i = 0; i < count; i++) {
        _vertexArray->setBinormal(i, ((igVec3f *)bn->_data)[i]);
    }
    return g_resultSuccess;
}
}
}

