igMetaObject *g_igBlendMatrixSelect_metaObject;
igMetaField *g_igBlendMatrixSelect_blendMatrixIndicesMetaField;
igMetaField *g_igBlendMatrixSelect_skeletonTransformMetaField;
igMetaField *g_igBlendMatrixSelect_skeletonInverseTransformMetaField;

igMetaObject *igBlendMatrixSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixSelect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendMatrixSelect_EnsureRegistered();
    return g_igBlendMatrixSelect_metaObject;
}

int igBlendMatrixSelect_GetVTable(void) { struct Obj_1a4ba0 o; int *p = (int *)&o; int *q; int t;
 igObject_InitHeader((struct Obj_1a4ba0 *)p); o.vt = &g_igBlendMatrixSelect_vtable[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0; o.f32 = 0; q = &o.f40; *q = 0;
 igMatrix44f_SetIdentity(o.sub1); igMatrix44f_SetIdentity(p + 27);
 t = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
 o.vt = &g_igBlendMatrixSelect_vtable[0]; igSmartPointer_igIntList_Destruct(q, -1); p = (int*)&o; FUN_0019c0e0((struct S_19c0e0 *)((struct Obj_1a4ba0 *)p), 0); return t; }

void igBlendMatrixSelect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixSelect_Register);
}

static igMetaObjectCallback g_igBlendMatrixSelect_callbackList[] = { igIntList_EnsureRegistered, 0 };

void igBlendMatrixSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatrixSelect_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igBlendMatrixSelect_GetMetaObject,
        "igBlendMatrixSelect",
        0xAC, /* instance size */
        igBlendMatrixSelect_GetVTable,
        &igBlendMatrixSelect_InitFields,
        0, /* extra callback item */
        g_igBlendMatrixSelect_callbackList /* callback list */
    );
}

void thunk_igBlendMatrixSelect_GetMetaObject(void) {
    igBlendMatrixSelect_GetMetaObject();
}

static FieldFactory g_igBlendMatrixSelect_ctorTable[] = {
    igObjectRefMetaField_Create,
    FUN_00188660,
    FUN_00188660,
};
static const char *g_igBlendMatrixSelect_fieldTable[] = {
    "_blendMatrixIndices",
    "_skeletonTransform",
    "_skeletonInverseTransform",
};
static igMetaField **g_igBlendMatrixSelect_fieldHandles[] = {
    &g_igBlendMatrixSelect_blendMatrixIndicesMetaField,
    &g_igBlendMatrixSelect_skeletonTransformMetaField,
    &g_igBlendMatrixSelect_skeletonInverseTransformMetaField,
};
static int g_igBlendMatrixSelect_fieldOffsets[] = {
    40,
    44,
    108,
};

void igBlendMatrixSelect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBlendMatrixSelect_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBlendMatrixSelect_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBlendMatrixSelect_fieldTable, g_igBlendMatrixSelect_fieldHandles, g_igBlendMatrixSelect_fieldOffsets, temp_s2);
}

