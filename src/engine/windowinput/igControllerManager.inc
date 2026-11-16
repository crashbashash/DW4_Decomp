igMetaObject *g_igControllerManager_metaObject;
igMetaField *g_igControllerManager_controllersMetaField;

igMetaObject *FUN_00146660(void) {
    if (g_igControllerManager_metaObject == 0) {
        g_igControllerManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igControllerManager_metaObject;
}

igMetaObject *igControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146700();
    return g_igControllerManager_metaObject;
}

void FUN_00146700(void)
{
    igMetaObject_RunStaticInit(igControllerManager_Register);
}

static igMetaObjectCallback g_igControllerManager_callbackList[] = { FUN_001463e0, 0 };

CallbackArray *igControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igControllerManager_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igControllerManager_GetMetaObject,
        "igControllerManager",
        0xC, /* instance size */
        0,
        &igControllerManager_InitFields,
        0, /* extra callback item */
        g_igControllerManager_callbackList /* callback list */
    );
}

void thunk_igControllerManager_GetMetaObject(void) {
    igControllerManager_GetMetaObject();
}

static FieldFactory g_igControllerManager_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igControllerManager_fieldTable[] = {
    "_controllers",
};
static igMetaField **g_igControllerManager_fieldHandles[] = {
    &g_igControllerManager_controllersMetaField,
};
static int g_igControllerManager_fieldOffsets[] = {
    8,
};

void igControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igControllerManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igControllerManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00146300();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igControllerManager_fieldTable, g_igControllerManager_fieldHandles, g_igControllerManager_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igControllerManager_metaObject) + 60) = (int)(&thunk_igPsx2ControllerManager_GetMetaObject);
}

