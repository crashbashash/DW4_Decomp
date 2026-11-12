igMetaObject *FUN_00359e60(void) {
    if (g_beMatCtrlSearchList_metaObject[0] == 0) {
        g_beMatCtrlSearchList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beMatCtrlSearchList_metaObject[0];
}

void *FUN_00359eb0(void) {
    unsigned char b;
    if (((void * *)g_beMatCtrlSearchList_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beMatCtrlSearchList_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00359f40();
done:
    return ((void * *)g_beMatCtrlSearchList_metaObject)[0];
}

int beMatCtrlSearchList_GetVTable(void) {
    struct Obj_359f00 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536b00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00359f40(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearchList_Register);
}

void *beMatCtrlSearchList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlSearchList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlSearchList_GetMetaObject,
        beMatCtrlSearchList_className,
        0x14, /* instance size */
        beMatCtrlSearchList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlSearchList_callbackList /* callback list */
    );
}

void beMatCtrlSearchList_GetMetaObject(void)
{
    FUN_00359eb0();
}

