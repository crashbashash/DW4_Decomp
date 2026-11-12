SFUN_0035b3d0 *FUN_0035b3d0(void) {
    if (DAT_005891e8[0] == 0 || !DAT_005891e8[0]->ok()) FUN_0035b460();
    return DAT_005891e8[0];
}

int beLuaDataObjectist_GetVTable(void) {
    struct Obj_35b420 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536820[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035b460(void)
{
    igMetaObject_RunStaticInit(beLuaDataObjectist_Register);
}

void *beLuaDataObjectist_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataObjectist_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataObjectist_GetMetaObject,
        beLuaDataObjectist_className,
        0x14, /* instance size */
        beLuaDataObjectist_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataObjectist_callbackList /* callback list */
    );
}

void beLuaDataObjectist_GetMetaObject(void)
{
    FUN_0035b3d0();
}

