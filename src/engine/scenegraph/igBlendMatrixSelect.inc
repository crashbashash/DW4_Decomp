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
 igObject_InitHeader((igObject *)(struct Obj_1a4ba0 *)p); o.vt = &g_igBlendMatrixSelect_vtable[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0; o.f32 = 0; q = &o.f40; *q = 0;
 igMatrix44f_SetIdentity((float *)o.sub1); igMatrix44f_SetIdentity((float *)(p + 27));
 t = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
 o.vt = &g_igBlendMatrixSelect_vtable[0]; igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)q, -1); p = (int*)&o; FUN_0019c0e0((struct S_19c0e0 *)((struct Obj_1a4ba0 *)p), 0); return t; }

void igBlendMatrixSelect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixSelect_Register);
}

static igMetaObjectCallback g_igBlendMatrixSelect_callbackList[] = { igIntList_EnsureRegistered, 0 };

CallbackArray *igBlendMatrixSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatrixSelect_metaObject,
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        igBlendMatrixSelect_GetMetaObjectFunction,
        "igBlendMatrixSelect",
        0xAC, /* instance size */
        igBlendMatrixSelect_GetVTable,
        &igBlendMatrixSelect_InitFields,
        0, /* extra callback item */
        g_igBlendMatrixSelect_callbackList /* callback list */
    );
}

void igBlendMatrixSelect_GetMetaObjectFunction(void) {
    igBlendMatrixSelect_GetMetaObject();
}

static FieldFactory g_igBlendMatrixSelect_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
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
    int base;
    void *blendMatrixIndicesField;
    void *meta;

    meta = (void *)g_igBlendMatrixSelect_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igBlendMatrixSelect_ctorTable, 3);
    blendMatrixIndicesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)blendMatrixIndicesField)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)blendMatrixIndicesField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igBlendMatrixSelect_fieldTable, g_igBlendMatrixSelect_fieldHandles, g_igBlendMatrixSelect_fieldOffsets, base);
}

