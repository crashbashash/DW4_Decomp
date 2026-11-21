igMetaObject *g_igAnimationSystem_metaObject;
igMetaField *g_igAnimationSystem_animHierarchyMetaField;

igMetaObject *igAnimationSystem_GetOrCreateMetaObject(void) {
    if (g_igAnimationSystem_metaObject == 0) {
        g_igAnimationSystem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationSystem_metaObject;
}

igMetaObject *igAnimationSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSystem_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationSystem_EnsureRegistered();
    return g_igAnimationSystem_metaObject;
}

void igAnimationSystem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationSystem_Register);
}

static igMetaObjectCallback g_igAnimationSystem_callbackList[] = { igAnimationHierarchy_EnsureRegistered, 0 };

CallbackArray *igAnimationSystem_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAnimationSystem_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igAnimationSystem_GetMetaObjectFunction,
        "igAnimationSystem",
        0x10, /* instance size */
        0,
        &igAnimationSystem_InitFields,
        0, /* extra callback item */
        g_igAnimationSystem_callbackList /* callback list */
    );
}

void igAnimationSystem_GetMetaObjectFunction(void) {
    igAnimationSystem_GetMetaObject();
}

static FieldFactory g_igAnimationSystem_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimationSystem_fieldTable[] = {
    "_animHierarchy",
};
static igMetaField **g_igAnimationSystem_fieldHandles[] = {
    &g_igAnimationSystem_animHierarchyMetaField,
};
static int g_igAnimationSystem_fieldOffsets[] = {
    12,
};

void igAnimationSystem_InitFields(void) {
    int base;
    void *animHierarchyField;
    void *meta;

    meta = (void *)g_igAnimationSystem_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationSystem_ctorTable, 1);
    animHierarchyField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)animHierarchyField)->_metaObject = (int)igAnimationHierarchy_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationSystem_fieldTable, g_igAnimationSystem_fieldHandles, g_igAnimationSystem_fieldOffsets, base);
}

