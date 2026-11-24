igMetaObject *g_igViewerAction_metaObject;
igMetaField *g_igViewerAction_refMetaField;
igMetaField *g_igViewerAction_functionMetaField;

igViewerAction *igViewerAction_Create(int allocator) {
    igViewerAction_EnsureRegistered();
    return (igViewerAction *)igMetaObject_CreateInstance(g_igViewerAction_metaObject, (igMemoryPoolView *)allocator);
}

void *igViewerAction_GetMetaObject(void) {
    igMetaObject *g = g_igViewerAction_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igViewerAction_EnsureRegistered();
    }
    return g_igViewerAction_metaObject;
}

int igViewerAction_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igViewerAction_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igViewerAction_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewerAction_Register);
}

static igMetaObjectCallback g_igViewerAction_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, 0 };

CallbackArray *igViewerAction_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerAction_metaObject,
        Gap::Gui::igAction::arkRegisterInternal,
        Gap::Gui::igAction::getClassMeta,
        igViewerAction_GetMetaObjectFunction,
        "igViewerAction",
        0x18, /* instance size */
        igViewerAction_GetVTable,
        &igViewerAction_InitFields,
        0, /* extra callback item */
        g_igViewerAction_callbackList /* callback list */
    );
}

void igViewerAction_GetMetaObjectFunction(void) {
    igViewerAction_GetMetaObject();
}

static FieldFactory g_igViewerAction_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStructMetaField_Create,
};
static const char *g_igViewerAction_fieldTable[] = {
    "_ref",
    "_function",
};
static igMetaField **g_igViewerAction_fieldHandles[] = {
    &g_igViewerAction_refMetaField,
    &g_igViewerAction_functionMetaField,
};
static int g_igViewerAction_fieldOffsets[] = {
    8,
    12,
};

void igViewerAction_InitFields(void) {
    void *f2;
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewerAction_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerAction_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1) + 60) = 0;
    f2 = igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1);
    *(short *)((char *)f2 + 20) = 0xC;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerAction_fieldTable, g_igViewerAction_fieldHandles, g_igViewerAction_fieldOffsets, temp_s2);
}

