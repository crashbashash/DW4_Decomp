int FUN_0019ca30(void) {
    if (DAT_00561828[0] == 0) {
        DAT_00561828[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561828[0];
}

igMetaObject *igNodeListList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019cb10();
    return g_igNodeListList_metaObject[0];
}

int igNodeListList_GetVTable(void) {
    Obj_19cad0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0052ab90[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0019cb10(void)
{
    igMetaObject_RunStaticInit(igNodeListList_Register);
}

void igNodeListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNodeListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNodeListList_GetMetaObject,
        igNodeListList_className,
        0x14, /* instance size */
        igNodeListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNodeListList_callbackList /* callback list */
    );
}

void thunk_igNodeListList_GetMetaObject(void) {
    igNodeListList_GetMetaObject();
}

