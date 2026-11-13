igMetaObject *FUN_00357ee0(void) {
    if (g_beMessengerWorkList_metaObject[0] == 0) {
        g_beMessengerWorkList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerWorkList_metaObject[0];
}

void *FUN_00357f30(void) {
    igMetaObject *g = g_beMessengerWorkList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00357fc0();
    }
    return g_beMessengerWorkList_metaObject[0];
}

int beMessengerWorkList_GetVTable(void) {
    struct Obj_357f80 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00357fc0(void)
{
    igMetaObject_RunStaticInit(beMessengerWorkList_Register);
}

void *beMessengerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerWorkList_GetMetaObject,
        beMessengerWorkList_className,
        0x14, /* instance size */
        beMessengerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerWorkList_callbackList /* callback list */
    );
}

void beMessengerWorkList_GetMetaObject(void)
{
    FUN_00357f30();
}

