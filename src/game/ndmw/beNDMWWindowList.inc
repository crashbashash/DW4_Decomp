int FUN_003b1be0(void) {
    if (((int *)DAT_0058a9a8)[0] == 0) {
        ((int *)DAT_0058a9a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058a9a8)[0];
}

SFUN_003b1c30 *FUN_003b1c30(void) {
    if (DAT_0058a9a8[0] == 0 || !DAT_0058a9a8[0]->ok()) FUN_003b1cc0();
    return DAT_0058a9a8[0];
}

int beNDMWWindowList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053ddc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

int FUN_003b1d70(void) {
    if (DAT_0058a9b0[0] == 0) {
        DAT_0058a9b0[0] = igMetaEnum_Create(&DAT_00510ab0[0], &DAT_004c9410[0], &DAT_004c9440[0], 0xB);
    }
    return DAT_0058a9b0[0];
}

