int FUN_00146660(void) {
    if (DAT_0055f698[0] == 0) {
        DAT_0055f698[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f698[0];
}

igMetaObject *igControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146700();
    return g_igControllerManager_metaObject[0];
}

void FUN_00146700(void)
{
    igMetaObject_RunStaticInit(igControllerManager_Register);
}

void igControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igControllerManager_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igControllerManager_GetMetaObject,
        igControllerManager_className,
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

void igControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f698[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487268[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00146300();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487270[0], &DAT_00487278[0], &DAT_00487280[0], temp_s2);
    *(int *)((char *)(DAT_0055f698[0]) + 60) = (int)(&thunk_igPsx2ControllerManager_GetMetaObject);
}

