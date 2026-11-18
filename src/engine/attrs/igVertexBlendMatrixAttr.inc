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
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
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
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
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
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    meta = g_igVertexBlendMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexBlendMatrixAttr_ctorTable, 2);
    field = (int)igMetaObject_GetFieldAt(meta, base);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows((float *)&o1, (igVec4f *)&o2, (igVec4f *)&o3, (igVec4f *)&o4, (igVec4f *)&o5);
    FUN_0018c640(field, &o1);
    tf = (int)igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)tf)->_invarianceFunction = (int)&igVertexBlendMatrixAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igVertexBlendMatrixAttr_fieldTable, g_igVertexBlendMatrixAttr_fieldHandles, g_igVertexBlendMatrixAttr_fieldOffsets, base);
}

void igMatrix44f_FromRows(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                          const igVec4f *row3) {
    matrix[0] = row0->x;
    matrix[1] = row0->y;
    matrix[2] = row0->z;
    matrix[3] = row0->w;
    matrix[4] = row1->x;
    matrix[5] = row1->y;
    matrix[6] = row1->z;
    matrix[7] = row1->w;
    matrix[8] = row2->x;
    matrix[9] = row2->y;
    matrix[10] = row2->z;
    matrix[11] = row2->w;
    matrix[12] = row3->x;
    matrix[13] = row3->y;
    matrix[14] = row3->z;
    matrix[15] = row3->w;
}

