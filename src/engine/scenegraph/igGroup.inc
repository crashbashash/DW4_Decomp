igGroup *igGroup_CreateInstance(int allocator) {
    igGroup_EnsureRegistered();
    return (igGroup *)igMetaObject_CreateInstance((igMetaObject *)g_igGroup_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igGroup_GetOrCreateMetaObject(void) {
    if (g_igGroup_metaObject == 0) {
        g_igGroup_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGroup_metaObject;
}

igMetaObject *igGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGroup_EnsureRegistered();
    return g_igGroup_metaObject;
}

int igGroup_GetVTable(void) {
    struct Obj_19f2b0 obj;
    int temp_s0;

    igObject_InitHeader((igObject *)&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.vt = (&g_igGroup_vtable[0]);
    obj.f1C = 0;
    temp_s0 = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = (&g_igGroup_vtable[0]);
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)&obj.f1C, -1);
    igNode_Destroy((igNode *)&obj, 0);
    return temp_s0;
}

void igGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igGroup_Register);
}

static igMetaObjectCallback g_igGroup_callbackList[] = { igNodeList_EnsureRegistered, 0 };

CallbackArray *igGroup_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGroup_metaObject,
        igNode_Register,
        igNode_GetPublishedMetaObject,
        igGroup_GetMetaObjectFunction,
        "igGroup",
        0x20, /* instance size */
        igGroup_GetVTable,
        &igGroup_InitFields,
        0, /* extra callback item */
        g_igGroup_callbackList /* callback list */
    );
}

void igGroup_GetMetaObjectFunction(void) {
    igGroup_GetMetaObject();
}

static FieldFactory g_igGroup_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igGroup_fieldTable[] = {
    "_childList",
};
static igMetaField **g_igGroup_fieldHandles[] = {
    &g_igGroup_childListMetaField,
};
static int g_igGroup_fieldOffsets[] = {
    28,
};

void igGroup_InitFields(void) {
    int base;
    void *childListField;
    void *meta;

    meta = (void *)g_igGroup_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igGroup_ctorTable, 1);
    childListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)childListField)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igMetaField *)childListField)->_resetMethod = 3;
    ((igRefMetaField *)childListField)->_construct = 1;
    ((igMetaField *)childListField)->_deepCopyMethod = 0;
    ((igMetaField *)childListField)->_shallowCopyMethod = 2;
    igMetaObject_NameFields((igMetaObject *)meta, g_igGroup_fieldTable, g_igGroup_fieldHandles, g_igGroup_fieldOffsets, base);
}

