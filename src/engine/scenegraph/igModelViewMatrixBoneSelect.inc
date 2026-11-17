igModelViewMatrixBoneSelect *igModelViewMatrixBoneSelect_CreateInstance(int allocator) {
    igModelViewMatrixBoneSelect_EnsureRegistered();
    return (igModelViewMatrixBoneSelect *)igMetaObject_CreateInstance((igMetaObject *)g_igModelViewMatrixBoneSelect_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igModelViewMatrixBoneSelect_metaObject;
igMetaField *g_igModelViewMatrixBoneSelect_matrixIndexMetaField;

igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixBoneSelect_EnsureRegistered();
    return g_igModelViewMatrixBoneSelect_metaObject;
}

int igModelViewMatrixBoneSelect_GetVTable(void) {
    union U_19d480 u;
    int temp_s0;

    igObject_InitHeader((igObject *)u.b);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[7] = 0;
    u.w[0] = (int)(&g_igModelViewMatrixBoneSelect_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.w[0] = (int)(&g_igModelViewMatrixBoneSelect_vtable[0]);
    igGroup_Destroy((igGroup *)&u.w[0], 0);
    return temp_s0;
}

void igModelViewMatrixBoneSelect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixBoneSelect_Register);
}

CallbackArray *igModelViewMatrixBoneSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixBoneSelect_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelect_GetMetaObject,
        "igModelViewMatrixBoneSelect",
        0x24, /* instance size */
        igModelViewMatrixBoneSelect_GetVTable,
        &igModelViewMatrixBoneSelect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igModelViewMatrixBoneSelect_GetMetaObject(void) {
    igModelViewMatrixBoneSelect_GetMetaObject();
}

static FieldFactory g_igModelViewMatrixBoneSelect_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igModelViewMatrixBoneSelect_fieldTable[] = {
    "_matrixIndex",
};
static igMetaField **g_igModelViewMatrixBoneSelect_fieldHandles[] = {
    &g_igModelViewMatrixBoneSelect_matrixIndexMetaField,
};
static int g_igModelViewMatrixBoneSelect_fieldOffsets[] = {
    32,
};

void igModelViewMatrixBoneSelect_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igModelViewMatrixBoneSelect_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igModelViewMatrixBoneSelect_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igModelViewMatrixBoneSelect_fieldTable, g_igModelViewMatrixBoneSelect_fieldHandles, g_igModelViewMatrixBoneSelect_fieldOffsets, temp_s1);
}

