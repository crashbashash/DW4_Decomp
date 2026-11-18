igAttrSet *igAttrSet_CreateInstance(int allocator) {
    igAttrSet_EnsureRegistered();
    return (igAttrSet *)igMetaObject_CreateInstance((igMetaObject *)g_igAttrSet_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igAttrSet_GetOrCreateMetaObject(void) {
    if (g_igAttrSet_metaObject == 0) {
        g_igAttrSet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrSet_metaObject;
}

igMetaObject *igAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrSet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrSet_EnsureRegistered();
    return g_igAttrSet_metaObject;
}

int igAttrSet_GetVTable(void) {
    Obj_1a5e10 o;
    int r;

    igObject_InitHeader((igObject *)&o);
    o.w[1] = 0;
    o.w[2] = 0;
    o.w[3] = 0;
    o.w[6] = 0;
    o.vt = &g_igAttrSet_vtable[0];
    o.s = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igAttrSet_vtable[0];
    igSmartPointer_igAttrList_Destruct((igSmartPointer<igObject> *)&o.s, -1);
    igGroup_Destroy((igGroup *)&o, 0);
    return r;
}

void igAttrSet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrSet_Register);
}

static igMetaObjectCallback g_igAttrSet_callbackList[] = { igAttrList_EnsureRegistered, 0 };

CallbackArray *igAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrSet_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igAttrSet_GetMetaObjectFunction,
        "igAttrSet",
        0x28, /* instance size */
        igAttrSet_GetVTable,
        &igAttrSet_InitFields,
        0, /* extra callback item */
        g_igAttrSet_callbackList /* callback list */
    );
}

void igAttrSet_GetMetaObjectFunction(void) {
    igAttrSet_GetMetaObject();
}

static FieldFactory g_igAttrSet_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igAttrSet_fieldTable[] = {
    "_attributes",
    "_trigger",
};
static igMetaField **g_igAttrSet_fieldHandles[] = {
    &g_igAttrSet_attributesMetaField,
    &g_igAttrSet_triggerMetaField,
};
static int g_igAttrSet_fieldOffsets[] = {
    32,
    36,
};

void igAttrSet_InitFields(void) {
    int base;
    void *attributesField;
    void *meta;

    meta = (void *)g_igAttrSet_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAttrSet_ctorTable, 2);
    attributesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)attributesField)->_metaObject = (int)igAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)attributesField)->_construct = 1;
    ((igMetaField *)attributesField)->_deepCopyMethod = 0;
    ((igMetaField *)attributesField)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)meta, g_igAttrSet_fieldTable, g_igAttrSet_fieldHandles, g_igAttrSet_fieldOffsets, base);
}

