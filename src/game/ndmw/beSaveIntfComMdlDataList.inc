int FUN_003bc580(void) {
    if (((int *)DAT_0058b0a8)[0] == 0) {
        ((int *)DAT_0058b0a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b0a8)[0];
}

void *FUN_003bc5d0(void) {
    struct G *g = DAT_0058b0a8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003bc660();
    }
    return DAT_0058b0a8[0];
}

int beSaveIntfComMdlDataList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053d890[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003bc660(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlDataList_Register);
}

void *beSaveIntfComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveIntfComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSaveIntfComMdlDataList_GetMetaObject,
        beSaveIntfComMdlDataList_className,
        0x14, /* instance size */
        beSaveIntfComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSaveIntfComMdlDataList_callbackList /* callback list */
    );
}

void beSaveIntfComMdlDataList_GetMetaObject(void)
{
    FUN_003bc5d0();
}

