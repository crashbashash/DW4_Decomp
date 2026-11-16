igMetaObject *g_beFontGeomAttrPairList_metaObject;

igMetaObject *beFontGeomAttrPairList_GetOrCreateMetaObject(void) {
    if (g_beFontGeomAttrPairList_metaObject == 0) {
        g_beFontGeomAttrPairList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beFontGeomAttrPairList_metaObject;
}

void *beFontGeomAttrPairList_GetMetaObject(void) {
    igMetaObject *g = g_beFontGeomAttrPairList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFontGeomAttrPairList_EnsureRegistered();
    }
    return g_beFontGeomAttrPairList_metaObject;
}

int beFontGeomAttrPairList_GetVTable(void) {
    struct Obj_362400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beFontGeomAttrPairList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beFontGeomAttrPairList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPairList_Register);
}

static igMetaObjectCallback g_beFontGeomAttrPairList_callbackList[] = { beFontGeomAttrPair_EnsureRegistered, 0 };

void *beFontGeomAttrPairList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontGeomAttrPairList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beFontGeomAttrPairList_GetMetaObjectFunction,
        "beFontGeomAttrPairList",
        0x14, /* instance size */
        beFontGeomAttrPairList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontGeomAttrPairList_callbackList /* callback list */
    );
}

void beFontGeomAttrPairList_GetMetaObjectFunction(void)
{
    beFontGeomAttrPairList_GetMetaObject();
}

