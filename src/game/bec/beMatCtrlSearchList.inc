igMetaObject *g_beMatCtrlSearchList_metaObject;

igMetaObject *beMatCtrlSearchList_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlSearchList_metaObject == 0) {
        g_beMatCtrlSearchList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMatCtrlSearchList_metaObject;
}

void *beMatCtrlSearchList_GetMetaObject(void) {
    unsigned char b;
    if (g_beMatCtrlSearchList_metaObject != 0) {
        b = (g_beMatCtrlSearchList_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beMatCtrlSearchList_EnsureRegistered();
done:
    return g_beMatCtrlSearchList_metaObject;
}

int beMatCtrlSearchList_GetVTable(void) {
    beMatCtrlSearchList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMatCtrlSearchList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beMatCtrlSearchList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearchList_Register);
}

static igMetaObjectCallback g_beMatCtrlSearchList_callbackList[] = { beMatCtrlSearch_EnsureRegistered, 0 };

CallbackArray *beMatCtrlSearchList_Register(void) {
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

