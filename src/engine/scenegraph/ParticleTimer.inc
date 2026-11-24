namespace Gap {
namespace Sg {

/* The `_geoSet` field is added to the metaobject at run time (userRegister), so its place in an igGeometry is the
 * handle's offset. The sorter reads the handle as a C datum. */
static inline igGeometrySetAttr *geometrySetOf(igGeometry *geometry)
{
    return *(igGeometrySetAttr **)((char *)geometry + ((igMetaField *)DAT_00562768[0])->_offset);
}

/* The set draws through the render list the flags ask for: 2 with USE_RENDER_LIST_DELETE_ORIGINAL, 1 with USE_RENDER_LIST. */
static inline void setRenderListState(igGeometrySetAttr *geoSet, int flags)
{
    if (flags & 8) {
        geoSet->_renderListState = 2;
    } else if (flags & 4) {
        geoSet->_renderListState = 1;
    } else {
        geoSet->_renderListState = 0;
    }
}

void igGeometry::userRegister() {
    FieldHolder field;
    char *name;
    ObjectRefFieldView *held;
    if (((ObjectRefFieldView * *)DAT_00562768)[0] == 0) {
        field.p = (ObjectRefFieldView *)igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
        ((ObjectRefFieldView * *)DAT_00562768)[0] = field.p;
        name = internText("_geoSet");
        ((Gap::Core::igMetaField *)field.p)->setFieldName((void **)&name);
        if (name != 0) {
            int *header = (int *)name - 2;
            int count = ((int *)name)[-1] - 1;
            ((int *)name)[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
            }
        }
        field.p->_flag52 = 1;
        field.p->_flag38 = 0;
        field.p->_metaObject = (int)Gap::Attrs::igGeometrySetAttr::getClassTypeSafe();
        igMetaObject_AddFieldAndFinalize(_Meta, field.p);
        held = field.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)held);
            }
        }
    }
}

void igGeometry::userPostLoad()
{
    igAttrSet::userPostLoad();
    igGeometrySetAttr *geoSet = geometrySetOf(this);
    int current = _flags;
    setRenderListState(geoSet, current);
}

void igGeometry::setFlags(int flags)
{
    _flags = flags;
    igGeometrySetAttr *geoSet = geometrySetOf(this);
    setRenderListState(geoSet, flags);
}

void igGeometry::setFlags(int flags, const bool b)
{
    if (b) {
        _flags |= flags;
    } else {
        _flags &= ~flags;
    }
    igGeometrySetAttr *geoSet = geometrySetOf(this);
    int current = _flags;
    setRenderListState(geoSet, current);
}

void igGeometry::transform(const igMatrix44f &matrix)
{
    igAttrList *attrs = _attributes;
    unsigned int count = attrs->getCount();
    for (unsigned int i = 0; i < count; i++) {
        igAttr *attr = attrs->get(i);
        if (attr != 0 && attr->isOfType(igGeometryAttr::getClassMeta())) {
            igGeometryAttr *geometry = (igGeometryAttr *)attr;
            if (geometry->_vertexArray->getVertexFormat().getBlendWeightCount() == 0) {
                geometry->transform(matrix);
            }
        }
    }
}



/* Triangle count of the geometry attributes: triangle lists (_primType 3) add one per primitive, triangle
 * strips (4) add the vertex count less two per strip. */
unsigned int igGeometry::getTotalTriangles() const
{
    /* matching construct: declaration order sets the register colours (attrs last) */
    unsigned int triangles;
    unsigned int count;
    unsigned int i;
    igGeometryAttr *geometry;
    igAttrList *attrs;

    attrs = _attributes;
    triangles = 0;
    count = attrs->getCount();
    i = 0;
    /* matching construct: retail enters the loop through a zero-trip guard placed after the return (as igGroup::userPostLoad) */
    goto guard;
    next:
    geometry = (igGeometryAttr *)attrs->get(i);
    if (geometry->_primType == 3) {
        triangles += geometry->_numPrims;
    } else if (geometry->_primType == 4) {
        triangles += geometry->_vertexArray->_numVerts - geometry->_numPrims * 2;
    }
    i++;
    test:
    if (i < count) goto next;
    done:
    return triangles;
    guard:
    if (i < count) goto test;
    goto done;
}

void igGeometry::reset()
{
    unsigned int count = _attributes->getCount();
    for (unsigned int i = 0; i < count; i++) {
        _attributes->get(i)->reset();
    }
    igGeometrySetAttr *geoSet = geometrySetOf(this);
    if (geoSet != 0) {
        geoSet->reset();
    }
}
}
}

void FUN_001c5660(Z_1c5660 *arg0, int arg1, int arg2) {
    unsigned int cnt;
    unsigned int i;
    Item_1c5660 *it;
    V_1c5660 *o;
    int cur;
    int a1;
    i = 0;
    cnt = arg0->f32->cnt;
    for (; i < cnt; i++) {
        it = arg0->f32->items[i];
        if (it != 0) {
            o = it->f12;
            if (o != 0) {
                cur = o->f20;
                if (arg2 != 0) {
                    a1 = cur | arg1;
                } else {
                    a1 = cur & ~(cur & ~arg1);
                }
                o->vX(a1);
            }
        }
    }
}

namespace Gap {
namespace Sg {

void igGraphPath::configure(igNode *root)
{
    _path->append(root);
}

void igGraphPath::configure(igGraphPath *init) {
    T_1c5740 *arg1 = (T_1c5740 *)init;
    ((DW4VC_72_0 *)(arg1->f))->vX();
    ((Gap::Core::igObject *)((U_1c5740 *)this)->f)->copy((Gap::Core::igObject *)arg1->f, 0);
}

void igGraphPath::configure(igNodeList *nodes) {
    List_1c5790 *l = (List_1c5790 *)_path.p;
    int n = l->n;
    int i;
    for (i = 0; i < n; i++) {
        T *old = l->arr[i];
        if (old) {
            --old->references;
            if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                igObject_Destroy((::igObject *)old);
        }
    }
    int n2 = l->n;
    int j;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->n = 0;
    _path->concatenate(nodes);
}

void igGraphPath::pushNode(int child)
{
    _path->append(((igGroup *)getTop())->getChild(child));
}

igNode *igGraphPath::popNode()
{
    if (!isTop()) {
        igNodeList *list = _path;
        igNode *top = list->get(list->getCount() - 1);
        /* matching construct: retail reads the count a second time, not through the inline accessor */
        int last = list->_count - 1;
        igObject::release(list->get(last));
        List_RemoveWordAt((::igDataList *)list, last);
        ((igNode **)list->_data)[list->_count] = 0;
        return top;
    }
    return 0;
}

igNode *igGraphPath::getTop() const
{
    return _path->get(_path->getCount() - 1);
}

bool igGraphPath::isTop() const
{
    return getDepth() == 1;
}

int igGraphPath::getDepth() const
{
    return _path->getCount();
}

void igGraphPath::getTransformMatrix(int arg1, igMatrix44f *arg2, long long arg3) const {
    int i;
    EE *e;

    igMatrix44f_SetIdentity((float *)arg2);
    for (i = 0; i < arg1; i++) {
        e = (EE *)((OO *)this)->list->items[i];
        if (igMetaObject_IsOfType((igMetaObject *)(((DW4VC_88_0 *)(e))->vX()), Gap::Sg::igTransform::getClassMeta()) != 0) {
            if (e->f96 == 0) {
                ((DW4VC_156_2 *)(e))->vX(arg3);
                igMatrix44f_PreMultiply((float *)arg2, (const float *)((char *)e + 0x20));
            }
        } else if (igMetaObject_IsOfType((igMetaObject *)(((DW4VC_88_0 *)(e))->vX()), (igMetaObject *)g_igTimeTransform_metaObject[0]) != 0) {
            arg3 = ((DW4VC_164_1 *)(e))->vX(arg3);
        }
    }
}
}
}

