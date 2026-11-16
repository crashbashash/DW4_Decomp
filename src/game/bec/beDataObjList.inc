igMetaObject *g_beDataObjList_metaObject;

void beDataObjList_Create(int arg0) {
    beDataObjList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589840, arg0);
}

igMetaObject *beDataObjList_GetOrCreateMetaObject(void) {
    if (g_beDataObjList_metaObject == 0) {
        g_beDataObjList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDataObjList_metaObject;
}

igMetaObject *beDataObjList_GetMetaObject(void) {
    if (g_beDataObjList_metaObject == 0 || !isValid(g_beDataObjList_metaObject)) beDataObjList_EnsureRegistered();
    return g_beDataObjList_metaObject;
}

int beDataObjList_GetVTable(void) {
    struct Obj_364130 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beDataObjList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beDataObjList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataObjList_Register);
}

static igMetaObjectCallback g_beDataObjList_callbackList[] = { igNamedObject_EnsureRegistered, 0 };

void *beDataObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjList_GetMetaObjectFunction,
        "beDataObjList",
        0x14, /* instance size */
        beDataObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataObjList_callbackList /* callback list */
    );
}

void beDataObjList_GetMetaObjectFunction(void)
{
    beDataObjList_GetMetaObject();
}

