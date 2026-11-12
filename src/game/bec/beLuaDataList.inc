int FUN_0035afc0(void) {
    if (((int *)DAT_005891d0)[0] == 0) {
        ((int *)DAT_005891d0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005891d0)[0];
}

G_35b010 *FUN_0035b010(void) {
    G_35b010 *g = DAT_005891d0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0035b0a0();
    return DAT_005891d0[0];
}

int beLuaDataList_GetVTable(void) {
    Obj_35b060 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005368f0[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035b0a0(void)
{
    igMetaObject_RunStaticInit(beLuaDataList_Register);
}

void *beLuaDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataList_GetMetaObject,
        beLuaDataList_className,
        0x14, /* instance size */
        beLuaDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataList_callbackList /* callback list */
    );
}

void beLuaDataList_GetMetaObject(void)
{
    FUN_0035b010();
}

