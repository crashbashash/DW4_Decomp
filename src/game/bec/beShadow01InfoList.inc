igMetaObject *FUN_003449b0(void) {
    if (g_beShadow01InfoList_metaObject[0] == 0) {
        g_beShadow01InfoList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beShadow01InfoList_metaObject[0];
}

void *FUN_00344a00(void) {
    igMetaObject *g = g_beShadow01InfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00344a90();
    }
    return g_beShadow01InfoList_metaObject[0];
}

int beShadow01InfoList_GetVTable(void) {
    Obj_344a50 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005391b0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00344a90(void)
{
    igMetaObject_RunStaticInit(beShadow01InfoList_Register);
}

void *beShadow01InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beShadow01InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beShadow01InfoList_GetMetaObject,
        beShadow01InfoList_className,
        0x14, /* instance size */
        beShadow01InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beShadow01InfoList_callbackList /* callback list */
    );
}

void beShadow01InfoList_GetMetaObject(void)
{
    FUN_00344a00();
}

