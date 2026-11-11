int FUN_00146300(void) {
    if (DAT_0055f608[0] == 0) {
        DAT_0055f608[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f608[0];
}

igMetaObject *igControllerList_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001463e0();
    return g_igControllerList_metaObject[0];
}

int igControllerList_GetVTable(void) {
    Obj_1463a0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00524f70[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001463e0(void)
{
    igMetaObject_RunStaticInit(igControllerList_Register);
}

void igControllerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igControllerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igControllerList_GetMetaObject,
        igControllerList_className,
        0x14, /* instance size */
        igControllerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igControllerList_callbackList /* callback list */
    );
}

void thunk_igControllerList_GetMetaObject(void) {
    igControllerList_GetMetaObject();
}

