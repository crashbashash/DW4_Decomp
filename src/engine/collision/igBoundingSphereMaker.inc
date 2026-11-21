igMetaObject *g_igBoundingSphereMaker_metaObject;
igMetaField *g_igBoundingSphereMaker_sphereMetaField;

igObject *igBoundingSphereMaker_Create(int arg0) {
    igBoundingSphereMaker_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igBoundingSphereMaker_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igBoundingSphereMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingSphereMaker_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoundingSphereMaker_EnsureRegistered();
    return g_igBoundingSphereMaker_metaObject;
}

int igBoundingSphereMaker_GetVTable(void) {
    union U_23aa60 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[8];
    u.vt = (int)&g_igBoundingSphereMaker_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igBoundingSphereMaker_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

void igBoundingSphereMaker_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoundingSphereMaker_Register);
}

static igMetaObjectCallback g_igBoundingSphereMaker_callbackList[] = { igSphere_EnsureRegistered, 0 };

CallbackArray *igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingSphereMaker_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igBoundingSphereMaker_GetMetaObjectFunction,
        "igBoundingSphereMaker",
        0xC, /* instance size */
        igBoundingSphereMaker_GetVTable,
        &igBoundingSphereMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingSphereMaker_callbackList /* callback list */
    );
}

void igBoundingSphereMaker_GetMetaObjectFunction(void) {
    igBoundingSphereMaker_GetMetaObject();
}

static FieldFactory g_igBoundingSphereMaker_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igBoundingSphereMaker_fieldTable[] = {
    "_sphere",
};
static igMetaField **g_igBoundingSphereMaker_fieldHandles[] = {
    &g_igBoundingSphereMaker_sphereMetaField,
};
static int g_igBoundingSphereMaker_fieldOffsets[] = {
    8,
};

void igBoundingSphereMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igBoundingSphereMaker_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBoundingSphereMaker_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igSphere_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBoundingSphereMaker_fieldTable, g_igBoundingSphereMaker_fieldHandles, g_igBoundingSphereMaker_fieldOffsets, temp_s2);
}

static inline igGeometryAttr *asGeometryAttr(igObject *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(g_igGeometryAttr_metaObject) != 0) return (igGeometryAttr *)o;
    return 0;
}

/* Ritter's bounding sphere: the farthest apart of the vertex pairs extreme in x, in y and in z gives a first
 * sphere, which a second pass over the vertices grows to take in each vertex still outside it. */
igSmartPointer<igSphere> FUN_0023ac20(igBoundingSphereMaker *self, igGeometry *geometry) {
    igSmartPointer<igSphere> sphere((igSphere *)FUN_00187e10(0), AdoptReference());
    igVec3f minX(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
    igVec3f minY(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
    igVec3f minZ(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
    igVec3f maxX(-3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f);
    igVec3f maxY(-3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f);
    igVec3f maxZ(-3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f);
    igObjectList *attributes = (igObjectList *)geometry->_attributes;
    int count = attributes->_count;
    int i;

    for (i = 0; i < count; i++) {
        igObject *object = ((igObject **)attributes->_data)[i];
        igGeometryAttr *attr = asGeometryAttr(object);
        if (attr != 0) {
            unsigned int vertexCount = ((igVertexArray *)attr->_vertexArray)->_numVerts;
            for (unsigned int v = 0; v < vertexCount; v++) {
                igVec3f p;
                ((igVertexArrayAccess *)attr->_vertexArray)->getPosition(v, &p);
                if (p[0] < minX[0]) minX = p;
                if (p[1] < minY[1]) minY = p;
                if (p[2] < minZ[2]) minZ = p;
                if (maxX[0] < p[0]) maxX = p;
                if (maxY[1] < p[1]) maxY = p;
                if (maxZ[2] < p[2]) maxZ = p;
            }
        }
    }
    /* matching construct: manual search — x's difference vector summed after y's and z's sums, spanX declared first */
    float spanX;
    igVec3f diameter = maxX - minX;
    float spanY = (maxY[0] - minY[0]) * (maxY[0] - minY[0]) + (maxY[1] - minY[1]) * (maxY[1] - minY[1]) + (maxY[2] - minY[2]) * (maxY[2] - minY[2]);
    float spanZ = (maxZ[0] - minZ[0]) * (maxZ[0] - minZ[0]) + (maxZ[1] - minZ[1]) * (maxZ[1] - minZ[1]) + (maxZ[2] - minZ[2]) * (maxZ[2] - minZ[2]);
    spanX = diameter.length2();
    if (spanX < spanY) {
        minX = minY;
        maxX = maxY;
        spanX = spanY;
    }
    if (spanX < spanZ) {
        minX = minZ;
        maxX = maxZ;
    }
    igVec3f center;
    center[0] = 0.5f * minX[0] + 0.5f * maxX[0];
    center[1] = 0.5f * minX[1] + 0.5f * maxX[1];
    center[2] = 0.5f * minX[2] + 0.5f * maxX[2];
    igVec3f toEdge;
    toEdge.subtract(center, maxX);
    float radiusSquared = toEdge.length2();
    float radius = sqrtf(radiusSquared);
    for (i = 0; i < count; i++) {
        igObject *object = ((igObject **)attributes->_data)[i];
        igGeometryAttr *attr = asGeometryAttr(object);
        if (attr != 0) {
            unsigned int vertexCount = ((igVertexArray *)attr->_vertexArray)->_numVerts;
            for (unsigned int v = 0; v < vertexCount; v++) {
                igVec3f p;
                ((igVertexArrayAccess *)attr->_vertexArray)->getPosition(v, &p);
                float dx = center[0] - p[0];
                float dy = center[1] - p[1];
                float dz = center[2] - p[2];
                float distanceSquared = dx * dx + dy * dy + dz * dz;
                if (radiusSquared < distanceSquared) {
                    float distance = sqrtf(distanceSquared);
                    radius = (radius + distance) / 2.0f;
                    float keep = radius / distance;
                    radiusSquared = radius * radius;
                    float move = 1.0f - keep;
                    /* matching construct: manual search — x read through the const operator[] is reloaded, y and z are reused */
                    center[0] = keep * center[0] + move * ((const igVec3f &)p)[0];
                    center[1] = keep * center[1] + move * p[1];
                    center[2] = keep * center[2] + move * p[2];
                }
            }
        }
    }
    sphere->_center = center;
    sphere->_radius = radius;
    return sphere;
}

void FUN_0023b110(void *arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        FUN_0018d630((igSphere *)(*(int *)((char *)(arg0) + 8)), (const float *)((char *)arg1 + 0x20));
    }
}

void FUN_0023b140(struct R *arg0, struct Q *arg1) {
    unsigned int var_s1;
    unsigned int var_s0;
    struct Ls *temp_v0;

    if (((Gap::Core::igObject *)arg1)->isOfType(g_igGroup_metaObject) != 0) {
        temp_v0 = arg1->f28;
        var_s1 = 0;
        if (temp_v0 != 0) {
            var_s1 = temp_v0->n;
        }
        var_s0 = 0;
        while (var_s0 < var_s1) {
            FUN_0023b140(arg0, arg1->f28->a[var_s0]);
            var_s0 += 1;
        }
    }
    if (((Gap::Core::igObject *)arg1)->isOfType(g_igGeometry_metaObject) != 0) {
        igSmartPointer<igSphere> sphere(FUN_0023ac20((igBoundingSphereMaker *)arg0, (igGeometry *)arg1));
        FUN_0018de10((igSphere *)arg0->f8, sphere);
    } else if (((Gap::Core::igObject *)arg1)->isOfType(g_igTransform_metaObject) != 0) {
        FUN_0023b110(arg0, arg1);
    }
}

igSmartPointer<igObject> FUN_0023b270(ObjectSlotOwner *owner, int value) {
    igSmartPointer<igObject> object(FUN_00187e10(0), AdoptReference());
    owner->setSlot(object);
    FUN_0023b140((R *)owner, (Q *)value);
    owner->clearSlot();
    return object;
}

void FUN_0023b3b0(RetainedList *list, RefCounted *object) {
    int at = list->_count;
    void *words = list->_words;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    List_InsertWords((igDataList *)words, at, 1, (const void *)&object);
    list->_count = list->_count + 1;
}

void FUN_0023b410(int *arg0, int arg1, int arg2, int arg3) {
    arg0[4] = arg1; arg0[5] = arg2; arg0[6] = arg3;
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)arg0[2]))->setCount(arg1 * arg2 * arg3);
}

