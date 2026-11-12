igMetaObject *FUN_003c3cb0(void) {
    if (g_beNDMWLoadIntf2DegiStateList_metaObject[0] == 0) {
        g_beNDMWLoadIntf2DegiStateList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWLoadIntf2DegiStateList_metaObject[0];
}

igMetaObject *beNDMWLoadIntf2DegiStateList_ResolveMetaObject(void) {
    if (g_beNDMWLoadIntf2DegiStateList_metaObject[0] == 0 || !isValid(g_beNDMWLoadIntf2DegiStateList_metaObject[0])) FUN_003c3d90();
    return g_beNDMWLoadIntf2DegiStateList_metaObject[0];
}

int beNDMWLoadIntf2DegiStateList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_0053cff0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_003c3d90(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateList_Register);
}

void *beNDMWLoadIntf2DegiStateList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiStateList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateList_GetMetaObject,
        beNDMWLoadIntf2DegiStateList_className,
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateList_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiStateList_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiStateList_ResolveMetaObject();
}

