igMetaObject *g_beMatCtrlSearchList_metaObject;

igMetaObject *beMatCtrlSearchList_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlSearchList_metaObject == 0) {
        g_beMatCtrlSearchList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlSearchList_metaObject;
}

void *beMatCtrlSearchList_GetMetaObject(void) {
    unsigned char b;
    if (((void * *)&g_beMatCtrlSearchList_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beMatCtrlSearchList_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beMatCtrlSearchList_EnsureRegistered();
done:
    return ((void * *)&g_beMatCtrlSearchList_metaObject)[0];
}

int beMatCtrlSearchList_GetVTable(void) {
    struct Obj_359f00 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beMatCtrlSearchList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beMatCtrlSearchList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearchList_Register);
}

static igMetaObjectCallback g_beMatCtrlSearchList_callbackList[] = { beMatCtrlSearch_EnsureRegistered, 0 };

void *beMatCtrlSearchList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlSearchList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlSearchList_GetMetaObjectFunction,
        "beMatCtrlSearchList",
        0x14, /* instance size */
        beMatCtrlSearchList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlSearchList_callbackList /* callback list */
    );
}

void beMatCtrlSearchList_GetMetaObjectFunction(void)
{
    beMatCtrlSearchList_GetMetaObject();
}

