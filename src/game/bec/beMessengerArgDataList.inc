int FUN_00358bf0(void) {
    if (((int *)DAT_00589030)[0] == 0) {
        ((int *)DAT_00589030)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589030)[0];
}

S_358c40 *FUN_00358c40(void) {
    S_358c40 *g = DAT_00589030[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00358cd0();
done:
    return DAT_00589030[0];
}

int beMessengerArgDataList_GetVTable(void) {
    struct Obj_358c90 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536d00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00358cd0(void)
{
    igMetaObject_RunStaticInit(beMessengerArgDataList_Register);
}

void *beMessengerArgDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerArgDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerArgDataList_GetMetaObject,
        beMessengerArgDataList_className,
        0x14, /* instance size */
        beMessengerArgDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerArgDataList_callbackList /* callback list */
    );
}

void beMessengerArgDataList_GetMetaObject(void)
{
    FUN_00358c40();
}

