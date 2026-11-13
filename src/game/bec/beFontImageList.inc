igMetaObject *FUN_00361750(void) {
    if (g_beFontImageList_metaObject[0] == 0) {
        g_beFontImageList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beFontImageList_metaObject[0];
}

igMetaObject *FUN_003617a0(void) {
    igMetaObject *g = g_beFontImageList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00361830();
done:
    return g_beFontImageList_metaObject[0];
}

int beFontImageList_GetVTable(void) {
    struct Obj_3617f0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535a90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00361830(void)
{
    igMetaObject_RunStaticInit(beFontImageList_Register);
}

void *beFontImageList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontImageList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beFontImageList_GetMetaObject,
        beFontImageList_className,
        0x14, /* instance size */
        beFontImageList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontImageList_callbackList /* callback list */
    );
}

void beFontImageList_GetMetaObject(void)
{
    FUN_003617a0();
}

