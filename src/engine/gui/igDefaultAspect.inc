igMetaObject *FUN_004516e0(void) {
    if (g_igDefaultAspect_metaObject[0] == 0) {
        g_igDefaultAspect_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igDefaultAspect_metaObject[0];
}

igMetaObject *igDefaultAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspect_EnsureRegistered();
    return g_igDefaultAspect_metaObject[0];
}

int igDefaultAspect_GetVTable(void) {
    Obj_451780 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541480[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541480[0];
    obj.release();
    return r;
}

void igDefaultAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspect_Register);
}

void igDefaultAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspect_metaObject,
        igGuiComponentAspect_Register,
        igGuiComponentAspect_GetPublishedMetaObject,
        thunk_igDefaultAspect_GetMetaObject,
        igDefaultAspect_className,
        0x2C, /* instance size */
        igDefaultAspect_GetVTable,
        &igDefaultAspect_InitFields,
        0, /* extra callback item */
        g_igDefaultAspect_callbackList /* callback list */
    );
}

void thunk_igDefaultAspect_GetMetaObject(void) {
    igDefaultAspect_GetMetaObject();
}

void igDefaultAspect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDefaultAspect_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igDefaultAspect_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00451950();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igDefaultAspect_fieldTable[0], &DAT_004d0770[0], &DAT_004d0778[0], temp_s2);
}

