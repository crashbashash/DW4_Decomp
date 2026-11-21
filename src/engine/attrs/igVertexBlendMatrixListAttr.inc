igMetaObject *g_igVertexBlendMatrixListAttr_metaObject;
igMetaField *g_igVertexBlendMatrixListAttr_matrixListMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_skeletonTransformMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_skeletonInverseTransformMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_matrixCacheMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_isSkeletonTransformIdentityMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_isSkeletonTransformSetMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_currentMatrixCountMetaField;

igVertexBlendMatrixListAttr *igVertexBlendMatrixListAttr_Create(igMemoryPoolView *pool) {
    igVertexBlendMatrixListAttr_EnsureRegistered();
    return (igVertexBlendMatrixListAttr *)igMetaObject_CreateInstance(g_igVertexBlendMatrixListAttr_metaObject, pool);
}

igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexBlendMatrixListAttr_EnsureRegistered();
    return g_igVertexBlendMatrixListAttr_metaObject;
}

int igVertexBlendMatrixListAttr_GetVTable(void) {
    union U_1309c0 u;
    int temp_s0;
    S_ref *q0;
    int pi = (int)u.b;
    igObject_InitHeader((igObject *)pi);
    u.vt = (int)&g_igVertexBlendMatrixListAttr_vtable[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    igMatrix44f_SetIdentity((float *)&u.b[28]);
    igMatrix44f_SetIdentity((float *)(pi + 92));
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00522630[4];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    return temp_s0;
}

void igVertexBlendMatrixListAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttr_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixListAttr_callbackList[] = { igMatrixObjectList_EnsureRegistered, 0 };

CallbackArray *igVertexBlendMatrixListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixListAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igVertexBlendMatrixListAttr_GetMetaObjectFunction,
        "igVertexBlendMatrixListAttr",
        0x9C, /* instance size */
        igVertexBlendMatrixListAttr_GetVTable,
        &igVertexBlendMatrixListAttr_InitFields,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttr_callbackList /* callback list */
    );
}

void igVertexBlendMatrixListAttr_GetMetaObjectFunction(void) {
    igVertexBlendMatrixListAttr_GetMetaObject();
}

static FieldFactory g_igVertexBlendMatrixListAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igVertexBlendMatrixListAttr_fieldTable[] = {
    "_matrixList",
    "_skeletonTransform",
    "_skeletonInverseTransform",
    "_matrixCache",
    "_isSkeletonTransformIdentity",
    "_isSkeletonTransformSet",
    "_currentMatrixCount",
};
static igMetaField **g_igVertexBlendMatrixListAttr_fieldHandles[] = {
    &g_igVertexBlendMatrixListAttr_matrixListMetaField,
    &g_igVertexBlendMatrixListAttr_skeletonTransformMetaField,
    &g_igVertexBlendMatrixListAttr_skeletonInverseTransformMetaField,
    &g_igVertexBlendMatrixListAttr_matrixCacheMetaField,
    &g_igVertexBlendMatrixListAttr_isSkeletonTransformIdentityMetaField,
    &g_igVertexBlendMatrixListAttr_isSkeletonTransformSetMetaField,
    &g_igVertexBlendMatrixListAttr_currentMatrixCountMetaField,
};
static int g_igVertexBlendMatrixListAttr_fieldOffsets[] = {
    24,
    28,
    92,
    16,
    12,
    13,
    20,
};

void igVertexBlendMatrixListAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    igMetaObject *meta;

    meta = g_igVertexBlendMatrixListAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexBlendMatrixListAttr_ctorTable, 7);
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igMatrixObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field3)->_construct = 1;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igMetaField *)field2)->_persistent = 0;
    ((igMetaField *)field2)->_isAlikeShallowMethod = 3;
    ((igMetaField *)(igMetaObject_GetFieldAt(meta, base + 4)))->_persistent = 0;
    ((igMetaField *)(igMetaObject_GetFieldAt(meta, base + 5)))->_persistent = 0;
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((Gap::Core::igIntMetaField *)field)->setDefault(-1);
    ((igMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igVertexBlendMatrixListAttr_fieldTable, g_igVertexBlendMatrixListAttr_fieldHandles, g_igVertexBlendMatrixListAttr_fieldOffsets, base);
}

