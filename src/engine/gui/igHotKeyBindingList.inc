int FUN_0044dab0(void) {
    if (DAT_0058c2b8[0] == 0) {
        DAT_0058c2b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c2b8[0];
}

igMetaObject *igHotKeyBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBindingList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBindingList_RunStaticInit();
    return g_igHotKeyBindingList_metaObject[0];
}

int igHotKeyBindingList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541bd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igHotKeyBindingList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBindingList_Register);
}

void igHotKeyBindingList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyBindingList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igHotKeyBindingList_GetMetaObject,
        igHotKeyBindingList_className,
        0x14, /* instance size */
        igHotKeyBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igHotKeyBindingList_callbackList /* callback list */
    );
}

void thunk_igHotKeyBindingList_GetMetaObject(void) {
    igHotKeyBindingList_GetMetaObject();
}

