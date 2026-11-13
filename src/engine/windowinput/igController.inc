igMetaObject *igController_GetMetaObject(void)
{
    igMetaObject *g = g_igController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146900();
    return g_igController_metaObject[0];
}

void FUN_00146900(void)
{
    igMetaObject_RunStaticInit(igController_Register);
}

void igController_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igController_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igController_GetMetaObject,
        igController_className,
        0x10, /* instance size */
        0,
        &igController_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igController_GetMetaObject(void) {
    igController_GetMetaObject();
}

void igController_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igController_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igController_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = igIntMetaField_GetDefaultDescriptor();
    *(char *)((char *)(temp_s1) + 53) = 1;
    *(char *)((char *)(temp_s1) + 64) = 1;
    *(char *)((char *)(temp_s1) + 65) = 1;
    igMetaObject_NameFields(temp_s0, &g_igController_fieldTable[0], &DAT_00487438[0], &DAT_00487440[0], temp_s2);
    *(int *)((char *)(g_igController_metaObject[0]) + 60) = (int)thunk_igPsx2Controller_GetMetaObject;
}

