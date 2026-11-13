igMetaObject *FUN_001e5150(void) {
    if (g_igDataPumpManager_metaObject[0] == 0) {
        g_igDataPumpManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDataPumpManager_metaObject[0];
}

igMetaObject *igDataPumpManager_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5280();
    return g_igDataPumpManager_metaObject[0];
}

int igDataPumpManager_GetVTable(void) {
    Obj_1e51f0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052baf0[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052baf0[0];
    obj.release();
    return r;
}

void FUN_001e5280(void)
{
    igMetaObject_RunStaticInit(igDataPumpManager_Register);
}

void igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataPumpManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpManager_GetMetaObject,
        igDataPumpManager_className,
        0xC, /* instance size */
        igDataPumpManager_GetVTable,
        &igDataPumpManager_InitFields,
        0, /* extra callback item */
        g_igDataPumpManager_callbackList /* callback list */
    );
}

void thunk_igDataPumpManager_GetMetaObject(void) {
    igDataPumpManager_GetMetaObject();
}

void igDataPumpManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDataPumpManager_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igDataPumpManager_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001e53c0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igDataPumpManager_fieldTable[0], &DAT_0048db98[0], &DAT_0048dba0[0], temp_s2);
}

