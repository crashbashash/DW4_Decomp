void beDataObjList_Create(int arg0) {
    FUN_00364170();
    igMetaObject_CreateInstance(*(int *)0x589840, arg0);
}

igMetaObject *FUN_00364090(void) {
    if (g_beDataObjList_metaObject[0] == 0) {
        g_beDataObjList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beDataObjList_metaObject[0];
}

igMetaObject *FUN_003640e0(void) {
    if (g_beDataObjList_metaObject[0] == 0 || !isValid(g_beDataObjList_metaObject[0])) FUN_00364170();
    return g_beDataObjList_metaObject[0];
}

int beDataObjList_GetVTable(void) {
    struct Obj_364130 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535530[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00364170(void)
{
    igMetaObject_RunStaticInit(beDataObjList_Register);
}

void *beDataObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjList_GetMetaObject,
        beDataObjList_className,
        0x14, /* instance size */
        beDataObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataObjList_callbackList /* callback list */
    );
}

void beDataObjList_GetMetaObject(void)
{
    FUN_003640e0();
}

