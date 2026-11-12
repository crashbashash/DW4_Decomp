void FUN_0013a320(int arg0) {
    FUN_0013a440();
    igMetaObject_CreateInstance(*(int *)0x55F418, arg0);
}

igMetaObject *FUN_0013a360(void) {
    if (g_igTextureList_metaObject[0] == 0) {
        g_igTextureList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTextureList_metaObject[0];
}

igMetaObject *igTextureList_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a440();
    return g_igTextureList_metaObject[0];
}

int igTextureList_GetVTable(void) {
    struct Obj_13a400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524650[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0013a440(void)
{
    igMetaObject_RunStaticInit(igTextureList_Register);
}

void igTextureList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igTextureList_GetMetaObject,
        igTextureList_className,
        0x14, /* instance size */
        igTextureList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureList_callbackList /* callback list */
    );
}

void thunk_igTextureList_GetMetaObject(void) {
    igTextureList_GetMetaObject();
}

