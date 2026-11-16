igMetaObject *g_beUnicodeObjList_metaObject;

igMetaObject *beUnicodeObjList_GetOrCreateMetaObject(void) {
    if (g_beUnicodeObjList_metaObject == 0) {
        g_beUnicodeObjList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beUnicodeObjList_metaObject;
}

igMetaObject *beUnicodeObjList_GetMetaObject(void)
{
    igMetaObject *g = g_beUnicodeObjList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beUnicodeObjList_EnsureRegistered();
    return g_beUnicodeObjList_metaObject;
}

int beUnicodeObjList_GetVTable(void) {
    struct Obj_361400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beUnicodeObjList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beUnicodeObjList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beUnicodeObjList_Register);
}

static igMetaObjectCallback g_beUnicodeObjList_callbackList[] = { beUnicodeObj_EnsureRegistered, 0 };

void *beUnicodeObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beUnicodeObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beUnicodeObjList_GetMetaObjectFunction,
        "beUnicodeObjList",
        0x14, /* instance size */
        beUnicodeObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beUnicodeObjList_callbackList /* callback list */
    );
}

void beUnicodeObjList_GetMetaObjectFunction(void)
{
    beUnicodeObjList_GetMetaObject();
}

