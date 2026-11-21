igMetaObject *g_igVertexBlendMatrixAttr_metaObject;
igMetaField *g_igVertexBlendMatrixAttr_mMetaField;
igMetaField *g_igVertexBlendMatrixAttr_blendMatIDMetaField;

igVertexBlendMatrixAttr *igVertexBlendMatrixAttr_Create(igMemoryPoolView *pool) {
    igVertexBlendMatrixAttr_EnsureRegistered();
    return (igVertexBlendMatrixAttr *)igMetaObject_CreateInstance(g_igVertexBlendMatrixAttr_metaObject, pool);
}

igMetaObject *igVertexBlendMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexBlendMatrixAttr_EnsureRegistered();
    return g_igVertexBlendMatrixAttr_metaObject;
}

int igVertexBlendMatrixAttr_GetVTable(void) {
    union U_130ca0 u;
    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igVertexBlendMatrixAttr_vtable[0]);
    igMatrix44f_SetIdentity((float *)&u.w[3]);
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igVertexBlendMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixAttr_Register);
}

CallbackArray *igVertexBlendMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igVertexBlendMatrixAttr_GetMetaObjectFunction,
        "igVertexBlendMatrixAttr",
        0x50, /* instance size */
        igVertexBlendMatrixAttr_GetVTable,
        &igVertexBlendMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVertexBlendMatrixAttr_GetMetaObjectFunction(void) {
    igVertexBlendMatrixAttr_GetMetaObject();
}

static FieldFactory g_igVertexBlendMatrixAttr_ctorTable[] = {
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)igUnsignedShortMetaField_Create,
};
static const char *g_igVertexBlendMatrixAttr_fieldTable[] = {
    "_m",
    "_blendMatID",
};
static igMetaField **g_igVertexBlendMatrixAttr_fieldHandles[] = {
    &g_igVertexBlendMatrixAttr_mMetaField,
    &g_igVertexBlendMatrixAttr_blendMatIDMetaField,
};
static int g_igVertexBlendMatrixAttr_fieldOffsets[] = {
    12,
    76,
};

void igVertexBlendMatrixAttr_InitFields(void) {
    int tf;
    int base;
    int field;
    igMetaObject *meta;

    meta = g_igVertexBlendMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexBlendMatrixAttr_ctorTable, 2);
    field = (int)igMetaObject_GetFieldAt(meta, base);
    ((Gap::Math::igMatrix44fMetaField *)field)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                   igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    tf = (int)igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)tf)->_invarianceFunction = (int)&igVertexBlendMatrixAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igVertexBlendMatrixAttr_fieldTable, g_igVertexBlendMatrixAttr_fieldHandles, g_igVertexBlendMatrixAttr_fieldOffsets, base);
}

void igMatrix44f_FromRows(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                          const igVec4f *row3) {
    matrix[0] = row0->vec[0];
    matrix[1] = row0->vec[1];
    matrix[2] = row0->vec[2];
    matrix[3] = row0->vec[3];
    matrix[4] = row1->vec[0];
    matrix[5] = row1->vec[1];
    matrix[6] = row1->vec[2];
    matrix[7] = row1->vec[3];
    matrix[8] = row2->vec[0];
    matrix[9] = row2->vec[1];
    matrix[10] = row2->vec[2];
    matrix[11] = row2->vec[3];
    matrix[12] = row3->vec[0];
    matrix[13] = row3->vec[1];
    matrix[14] = row3->vec[2];
    matrix[15] = row3->vec[3];
}

