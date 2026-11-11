int FUN_00450c70(void) {
    if (DAT_0058c548[0] == 0) {
        DAT_0058c548[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c548[0];
}

igMetaObject *igFieldChangeViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeViewList_EnsureRegistered();
    return g_igFieldChangeViewList_metaObject[0];
}

int igFieldChangeViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005419d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igFieldChangeViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeViewList_Register);
}

void igFieldChangeViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFieldChangeViewList_GetMetaObject,
        igFieldChangeViewList_className,
        0x14, /* instance size */
        igFieldChangeViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFieldChangeViewList_callbackList /* callback list */
    );
}

void thunk_igFieldChangeViewList_GetMetaObject(void) {
    igFieldChangeViewList_GetMetaObject();
}

