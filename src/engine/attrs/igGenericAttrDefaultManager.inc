void FUN_00137ab0(int arg0) {
    FUN_00137b80();
    igMetaObject_CreateInstance(*(int *)0x55F1C0, arg0);
}

igMetaObject *igGenericAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericAttrDefaultManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137b80();
    return g_igGenericAttrDefaultManager_metaObject[0];
}

int igGenericAttrDefaultManager_GetVTable(void) {
    struct O_137b40 o;
    int pad[2];
    igObject_InitHeader(&o);
    o.vt = DAT_00523a20;
    return *(int *)((char *)&o + *(int *)(g_objectSystem[0] + 916));
}

void FUN_00137b80(void)
{
    igMetaObject_RunStaticInit(igGenericAttrDefaultManager_Register);
}

void igGenericAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGenericAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        thunk_igGenericAttrDefaultManager_GetMetaObject,
        igGenericAttrDefaultManager_className,
        8, /* instance size */
        igGenericAttrDefaultManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGenericAttrDefaultManager_GetMetaObject(void) {
    igGenericAttrDefaultManager_GetMetaObject();
}

