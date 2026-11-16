igMetaObject *g_igGenericCapabilityManager_metaObject;

void FUN_0014f2c0(int arg0) {
    FUN_0014f390();
    igMetaObject_CreateInstance(g_igGenericCapabilityManager_metaObject, arg0);
}

igMetaObject *igGenericCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericCapabilityManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f390();
    return g_igGenericCapabilityManager_metaObject;
}

int igGenericCapabilityManager_GetVTable(void) {
    struct Obj_14f350 obj;
    igObject_InitHeader(&obj);
    obj.vt = &g_igGenericCapabilityManager_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0014f390(void)
{
    igMetaObject_RunStaticInit(igGenericCapabilityManager_Register);
}

void igGenericCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGenericCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        thunk_igGenericCapabilityManager_GetMetaObject,
        "igGenericCapabilityManager",
        8, /* instance size */
        igGenericCapabilityManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGenericCapabilityManager_GetMetaObject(void) {
    igGenericCapabilityManager_GetMetaObject();
}

