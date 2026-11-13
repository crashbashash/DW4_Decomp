igMetaObject *FUN_00358350(void) {
    if (g_beMessengerGroupList_metaObject[0] == 0) {
        g_beMessengerGroupList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerGroupList_metaObject[0];
}

void *FUN_003583a0(void) {
    igMetaObject *g = g_beMessengerGroupList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00358430();
    }
    return g_beMessengerGroupList_metaObject[0];
}

int beMessengerGroupList_GetVTable(void) {
    struct Obj_3583f0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536ea0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00358430(void)
{
    igMetaObject_RunStaticInit(beMessengerGroupList_Register);
}

void *beMessengerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerGroupList_GetMetaObject,
        beMessengerGroupList_className,
        0x14, /* instance size */
        beMessengerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerGroupList_callbackList /* callback list */
    );
}

void beMessengerGroupList_GetMetaObject(void)
{
    FUN_003583a0();
}

