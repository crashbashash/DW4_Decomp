igMetaObject *g_igViewerSceneInfoManagerController_metaObject;
igMetaField *g_igViewerSceneInfoManagerController_applicationMetaField;
igMetaField *g_igViewerSceneInfoManagerController_viewerRendererMetaField;

igMetaObject *FUN_0045a8c0(void) {
    if (g_igViewerSceneInfoManagerController_metaObject == 0) {
        g_igViewerSceneInfoManagerController_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerSceneInfoManagerController_metaObject;
}

void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    igMetaObject *g = g_igViewerSceneInfoManagerController_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045a9a0();
    }
    return g_igViewerSceneInfoManagerController_metaObject;
}

int igViewerSceneInfoManagerController_GetVTable(void) {
    struct Obj_45a8c0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewerSceneInfoManagerController_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_0045a9a0(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManagerController_Register);
}

static igMetaObjectCallback g_igViewerSceneInfoManagerController_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, FUN_0045b0d0, 0 };

CallbackArray *igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerSceneInfoManagerController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManagerController_GetMetaObject,
        "igViewerSceneInfoManagerController",
        0x14, /* instance size */
        igViewerSceneInfoManagerController_GetVTable,
        &igViewerSceneInfoManagerController_InitFields,
        0, /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList /* callback list */
    );
}

void thunk_igViewerSceneInfoManagerController_GetMetaObject(void) {
    igViewerSceneInfoManagerController_GetMetaObject();
}

static FieldFactory g_igViewerSceneInfoManagerController_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igViewerSceneInfoManagerController_fieldTable[] = {
    "_application",
    "_viewerRenderer",
};
static igMetaField **g_igViewerSceneInfoManagerController_fieldHandles[] = {
    &g_igViewerSceneInfoManagerController_applicationMetaField,
    &g_igViewerSceneInfoManagerController_viewerRendererMetaField,
};
static int g_igViewerSceneInfoManagerController_fieldOffsets[] = {
    12,
    16,
};

void igViewerSceneInfoManagerController_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewerSceneInfoManagerController_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerSceneInfoManagerController_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0045aaf0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerSceneInfoManagerController_fieldTable, g_igViewerSceneInfoManagerController_fieldHandles, g_igViewerSceneInfoManagerController_fieldOffsets, temp_s2);
}

