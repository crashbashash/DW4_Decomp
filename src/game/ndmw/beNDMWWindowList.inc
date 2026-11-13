igMetaObject *FUN_003b1be0(void) {
    if (g_beNDMWWindowList_metaObject[0] == 0) {
        g_beNDMWWindowList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWWindowList_metaObject[0];
}

igMetaObject *FUN_003b1c30(void) {
    if (g_beNDMWWindowList_metaObject[0] == 0 || !isValid(g_beNDMWWindowList_metaObject[0])) FUN_003b1cc0();
    return g_beNDMWWindowList_metaObject[0];
}

int beNDMWWindowList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053ddc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003b1cc0(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowList_Register);
}

void *beNDMWWindowList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWWindowList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWWindowList_GetMetaObject,
        beNDMWWindowList_className,
        0x14, /* instance size */
        beNDMWWindowList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWWindowList_callbackList /* callback list */
    );
}

void beNDMWWindowList_GetMetaObject(void)
{
    FUN_003b1c30();
}

int SubWnd_GetMetaEnum(void) {
    if (DAT_0058a9b0[0] == 0) {
        DAT_0058a9b0[0] = igMetaEnum_Create(&text_SubWnd[0], &DAT_004c9410[0], &DAT_004c9440[0], 0xB);
    }
    return DAT_0058a9b0[0];
}

