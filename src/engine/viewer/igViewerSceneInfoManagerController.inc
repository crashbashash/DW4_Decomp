igMetaObject *FUN_0045a8c0(void) {
    if (g_igViewerSceneInfoManagerController_metaObject[0] == 0) {
        g_igViewerSceneInfoManagerController_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    igMetaObject *g = g_igViewerSceneInfoManagerController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045a9a0();
    }
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

int igViewerSceneInfoManagerController_GetVTable(void) {
    struct Obj_45a8c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542540[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
}

void FUN_0045a9a0(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManagerController_Register);
}

void igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManagerController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManagerController_GetMetaObject,
        igViewerSceneInfoManagerController_className,
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

void igViewerSceneInfoManagerController_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewerSceneInfoManagerController_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewerSceneInfoManagerController_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0045aaf0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &g_igViewerSceneInfoManagerController_fieldTable[0], &DAT_004d0e78[0], &DAT_004d0e80[0], temp_s2);
}

