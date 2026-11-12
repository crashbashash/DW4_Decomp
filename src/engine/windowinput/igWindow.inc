void FUN_00145d00(int arg0) {
    FUN_00145de0();
    igMetaObject_CreateInstance(*(int *)0x55F5D8, arg0);
}

igMetaObject *FUN_00145d40(void) {
    if (g_igWindow_metaObject[0] == 0) {
        g_igWindow_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igWindow_metaObject[0];
}

igMetaObject *igWindow_GetMetaObject(void)
{
    igMetaObject *g = g_igWindow_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145de0();
    return g_igWindow_metaObject[0];
}

void FUN_00145de0(void)
{
    igMetaObject_RunStaticInit(igWindow_Register);
}

void igWindow_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igWindow_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igWindow_GetMetaObject,
        igWindow_className,
        8, /* instance size */
        0,
        FUN_00145e80,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igWindow_GetMetaObject(void) {
    igWindow_GetMetaObject();
}

igMetaObject *FUN_00145e70(void) {
    return g_igEventProducer_metaObject[0];
}

void FUN_00145e80(void) {
    *(int *)((char *)(g_igWindow_metaObject[0]) + 60) = (int)(&thunk_FUN_00146a60);
}

void thunk_FUN_00146a60(void) {
    FUN_00146a60();
}

int FUN_00145eb0(void) {
    if (DAT_0055f5e0[0] == 0) {
        DAT_0055f5e0[0] = igMetaEnum_Create(&DAT_004d64d8[0], &DAT_00486dd0[0], &DAT_00486f80[0], 0x69);
    }
    return DAT_0055f5e0[0];
}

